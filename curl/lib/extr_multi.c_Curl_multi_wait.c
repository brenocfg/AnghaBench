#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pollfd {unsigned int events; unsigned int revents; scalar_t__ fd; } ;
struct curl_waitfd {int events; unsigned short revents; scalar_t__ fd; } ;
struct Curl_multi {struct Curl_easy* easyp; scalar_t__ in_callback; } ;
struct Curl_easy {struct Curl_easy* next; } ;
typedef  scalar_t__ curl_socket_t ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLM_BAD_HANDLE ; 
 int /*<<< orphan*/  CURLM_OK ; 
 int /*<<< orphan*/  CURLM_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLM_RECURSIVE_API_CALL ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 int CURL_WAIT_POLLIN ; 
 int CURL_WAIT_POLLOUT ; 
 int CURL_WAIT_POLLPRI ; 
 int Curl_poll (struct pollfd*,unsigned int,int) ; 
 int /*<<< orphan*/  Curl_wait_ms (int) ; 
 int FALSE ; 
 int GETSOCK_READSOCK (unsigned int) ; 
 int GETSOCK_WRITESOCK (unsigned int) ; 
 int /*<<< orphan*/  GOOD_MULTI_HANDLE (struct Curl_multi*) ; 
 int MAX_SOCKSPEREASYHANDLE ; 
 int NUM_POLLS_ON_STACK ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLPRI ; 
 int TRUE ; 
 int /*<<< orphan*/  curl_multi_timeout (struct Curl_multi*,long*) ; 
 int /*<<< orphan*/  free (struct pollfd*) ; 
 struct pollfd* malloc (unsigned int) ; 
 int multi_getsock (struct Curl_easy*,scalar_t__*) ; 
 int /*<<< orphan*/  multi_timeout (struct Curl_multi*,long*) ; 

__attribute__((used)) static CURLMcode Curl_multi_wait(struct Curl_multi *multi,
                                 struct curl_waitfd extra_fds[],
                                 unsigned int extra_nfds,
                                 int timeout_ms,
                                 int *ret,
                                 bool extrawait) /* when no socket, wait */
{
  struct Curl_easy *data;
  curl_socket_t sockbunch[MAX_SOCKSPEREASYHANDLE];
  int bitmap;
  unsigned int i;
  unsigned int nfds = 0;
  unsigned int curlfds;
  bool ufds_malloc = FALSE;
  long timeout_internal;
  int retcode = 0;
  struct pollfd a_few_on_stack[NUM_POLLS_ON_STACK];
  struct pollfd *ufds = &a_few_on_stack[0];

  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  if(multi->in_callback)
    return CURLM_RECURSIVE_API_CALL;

  /* Count up how many fds we have from the multi handle */
  data = multi->easyp;
  while(data) {
    bitmap = multi_getsock(data, sockbunch);

    for(i = 0; i< MAX_SOCKSPEREASYHANDLE; i++) {
      curl_socket_t s = CURL_SOCKET_BAD;

      if(bitmap & GETSOCK_READSOCK(i)) {
        ++nfds;
        s = sockbunch[i];
      }
      if(bitmap & GETSOCK_WRITESOCK(i)) {
        ++nfds;
        s = sockbunch[i];
      }
      if(s == CURL_SOCKET_BAD) {
        break;
      }
    }

    data = data->next; /* check next handle */
  }

  /* If the internally desired timeout is actually shorter than requested from
     the outside, then use the shorter time! But only if the internal timer
     is actually larger than -1! */
  (void)multi_timeout(multi, &timeout_internal);
  if((timeout_internal >= 0) && (timeout_internal < (long)timeout_ms))
    timeout_ms = (int)timeout_internal;

  curlfds = nfds; /* number of internal file descriptors */
  nfds += extra_nfds; /* add the externally provided ones */

  if(nfds > NUM_POLLS_ON_STACK) {
    /* 'nfds' is a 32 bit value and 'struct pollfd' is typically 8 bytes
       big, so at 2^29 sockets this value might wrap. When a process gets
       the capability to actually handle over 500 million sockets this
       calculation needs a integer overflow check. */
    ufds = malloc(nfds * sizeof(struct pollfd));
    if(!ufds)
      return CURLM_OUT_OF_MEMORY;
    ufds_malloc = TRUE;
  }
  nfds = 0;

  /* only do the second loop if we found descriptors in the first stage run
     above */

  if(curlfds) {
    /* Add the curl handles to our pollfds first */
    data = multi->easyp;
    while(data) {
      bitmap = multi_getsock(data, sockbunch);

      for(i = 0; i< MAX_SOCKSPEREASYHANDLE; i++) {
        curl_socket_t s = CURL_SOCKET_BAD;

        if(bitmap & GETSOCK_READSOCK(i)) {
          ufds[nfds].fd = sockbunch[i];
          ufds[nfds].events = POLLIN;
          ++nfds;
          s = sockbunch[i];
        }
        if(bitmap & GETSOCK_WRITESOCK(i)) {
          ufds[nfds].fd = sockbunch[i];
          ufds[nfds].events = POLLOUT;
          ++nfds;
          s = sockbunch[i];
        }
        if(s == CURL_SOCKET_BAD) {
          break;
        }
      }

      data = data->next; /* check next handle */
    }
  }

  /* Add external file descriptions from poll-like struct curl_waitfd */
  for(i = 0; i < extra_nfds; i++) {
    ufds[nfds].fd = extra_fds[i].fd;
    ufds[nfds].events = 0;
    if(extra_fds[i].events & CURL_WAIT_POLLIN)
      ufds[nfds].events |= POLLIN;
    if(extra_fds[i].events & CURL_WAIT_POLLPRI)
      ufds[nfds].events |= POLLPRI;
    if(extra_fds[i].events & CURL_WAIT_POLLOUT)
      ufds[nfds].events |= POLLOUT;
    ++nfds;
  }

  if(nfds) {
    int pollrc;
    /* wait... */
    pollrc = Curl_poll(ufds, nfds, timeout_ms);

    if(pollrc > 0) {
      retcode = pollrc;
      /* copy revents results from the poll to the curl_multi_wait poll
         struct, the bit values of the actual underlying poll() implementation
         may not be the same as the ones in the public libcurl API! */
      for(i = 0; i < extra_nfds; i++) {
        unsigned short mask = 0;
        unsigned r = ufds[curlfds + i].revents;

        if(r & POLLIN)
          mask |= CURL_WAIT_POLLIN;
        if(r & POLLOUT)
          mask |= CURL_WAIT_POLLOUT;
        if(r & POLLPRI)
          mask |= CURL_WAIT_POLLPRI;

        extra_fds[i].revents = mask;
      }
    }
  }

  if(ufds_malloc)
    free(ufds);
  if(ret)
    *ret = retcode;
  if(!extrawait || extra_fds || curlfds)
    /* if any socket was checked */
    ;
  else {
    long sleep_ms = 0;

    /* Avoid busy-looping when there's nothing particular to wait for */
    if(!curl_multi_timeout(multi, &sleep_ms) && sleep_ms) {
      if(sleep_ms > timeout_ms)
        sleep_ms = timeout_ms;
      Curl_wait_ms((int)sleep_ms);
    }
  }

  return CURLM_OK;
}