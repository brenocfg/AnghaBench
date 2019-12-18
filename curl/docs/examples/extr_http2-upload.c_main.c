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
struct timeval {int tv_sec; long tv_usec; int member_1; int /*<<< orphan*/  member_0; } ;
struct input {int /*<<< orphan*/  hnd; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  scalar_t__ CURLMcode ;
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 int /*<<< orphan*/  CURLMOPT_MAX_HOST_CONNECTIONS ; 
 int /*<<< orphan*/  CURLMOPT_PIPELINING ; 
 scalar_t__ CURLM_OK ; 
 long CURLPIPE_MULTIPLEX ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int NUM_HANDLES ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_multi_fdset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * curl_multi_init () ; 
 int /*<<< orphan*/  curl_multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  curl_multi_timeout (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  setup (struct input*,int,char const*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
  struct input trans[NUM_HANDLES];
  CURLM *multi_handle;
  int i;
  int still_running = 0; /* keep number of running handles */
  const char *filename = "index.html";
  int num_transfers;

  if(argc > 1) {
    /* if given a number, do that many transfers */
    num_transfers = atoi(argv[1]);

    if(!num_transfers || (num_transfers > NUM_HANDLES))
      num_transfers = 3; /* a suitable low default */

    if(argc > 2)
      /* if given a file name, upload this! */
      filename = argv[2];
  }
  else
    num_transfers = 3;

  /* init a multi stack */
  multi_handle = curl_multi_init();

  for(i = 0; i<num_transfers; i++) {
    setup(&trans[i], i, filename);

    /* add the individual transfer */
    curl_multi_add_handle(multi_handle, trans[i].hnd);
  }

  curl_multi_setopt(multi_handle, CURLMOPT_PIPELINING, CURLPIPE_MULTIPLEX);

  /* We do HTTP/2 so let's stick to one connection per host */
  curl_multi_setopt(multi_handle, CURLMOPT_MAX_HOST_CONNECTIONS, 1L);

  /* we start some action by calling perform right away */
  curl_multi_perform(multi_handle, &still_running);

  while(still_running) {
    struct timeval timeout;
    int rc; /* select() return code */
    CURLMcode mc; /* curl_multi_fdset() return code */

    fd_set fdread;
    fd_set fdwrite;
    fd_set fdexcep;
    int maxfd = -1;

    long curl_timeo = -1;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    /* set a suitable timeout to play around with */
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    curl_multi_timeout(multi_handle, &curl_timeo);
    if(curl_timeo >= 0) {
      timeout.tv_sec = curl_timeo / 1000;
      if(timeout.tv_sec > 1)
        timeout.tv_sec = 1;
      else
        timeout.tv_usec = (curl_timeo % 1000) * 1000;
    }

    /* get file descriptors from the transfers */
    mc = curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);

    if(mc != CURLM_OK) {
      fprintf(stderr, "curl_multi_fdset() failed, code %d.\n", mc);
      break;
    }

    /* On success the value of maxfd is guaranteed to be >= -1. We call
       select(maxfd + 1, ...); specially in case of (maxfd == -1) there are
       no fds ready yet so we call select(0, ...) --or Sleep() on Windows--
       to sleep 100ms, which is the minimum suggested value in the
       curl_multi_fdset() doc. */

    if(maxfd == -1) {
#ifdef _WIN32
      Sleep(100);
      rc = 0;
#else
      /* Portable sleep for platforms other than Windows. */
      struct timeval wait = { 0, 100 * 1000 }; /* 100ms */
      rc = select(0, NULL, NULL, NULL, &wait);
#endif
    }
    else {
      /* Note that on some platforms 'timeout' may be modified by select().
         If you need access to the original value save a copy beforehand. */
      rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
    }

    switch(rc) {
    case -1:
      /* select error */
      break;
    case 0:
    default:
      /* timeout or readable/writable sockets */
      curl_multi_perform(multi_handle, &still_running);
      break;
    }
  }

  curl_multi_cleanup(multi_handle);

  for(i = 0; i<num_transfers; i++) {
    curl_multi_remove_handle(multi_handle, trans[i].hnd);
    curl_easy_cleanup(trans[i].hnd);
  }

  return 0;
}