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
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  enum HandleState { ____Placeholder_HandleState } HandleState ;
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 long CURLAUTH_BASIC ; 
 long CURLAUTH_NTLM ; 
 int /*<<< orphan*/  CURLOPT_FRESH_CONNECT ; 
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_HTTPAUTH ; 
 int /*<<< orphan*/  CURLOPT_HTTPGET ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_USERPWD ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  CURL_SOCKET_BAD ; 
 int FALSE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int INT_MAX ; 
 int MAX_EASY_HANDLES ; 
 int NeedSocketForNewHandle ; 
 int NoMoreHandles ; 
 int ReadyForNewHandle ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  abort_on_test_timeout () ; 
 long callback ; 
 int* counter ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** easy ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  msnprintf (char*,size_t,char*,char*) ; 
 int /*<<< orphan*/  multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_fdset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  multi_timeout (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int res ; 
 int /*<<< orphan*/  res_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_test (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/ * sockets ; 
 int /*<<< orphan*/  start_test_timing () ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 

int test(char *url)
{
  CURLM *multi = NULL;
  int running;
  int i;
  int num_handles = 0;
  enum HandleState state = ReadyForNewHandle;
  size_t urllen = strlen(url) + 4 + 1;
  char *full_url = malloc(urllen);

  start_test_timing();

  if(!full_url) {
    fprintf(stderr, "Not enough memory for full url\n");
    return TEST_ERR_MAJOR_BAD;
  }

  for(i = 0; i < MAX_EASY_HANDLES; ++i) {
    easy[i] = NULL;
    sockets[i] = CURL_SOCKET_BAD;
  }

  res_global_init(CURL_GLOBAL_ALL);
  if(res) {
    free(full_url);
    return res;
  }

  multi_init(multi);

#ifdef USE_PIPELINING
  multi_setopt(multi, CURLMOPT_PIPELINING, 1L);
  multi_setopt(multi, CURLMOPT_MAX_HOST_CONNECTIONS, 5L);
  multi_setopt(multi, CURLMOPT_MAX_TOTAL_CONNECTIONS, 10L);
#endif

  for(;;) {
    struct timeval interval;
    fd_set fdread;
    fd_set fdwrite;
    fd_set fdexcep;
    long timeout = -99;
    int maxfd = -99;
    bool found_new_socket = FALSE;

    /* Start a new handle if we aren't at the max */
    if(state == ReadyForNewHandle) {
      easy_init(easy[num_handles]);

      if(num_handles % 3 == 2) {
        msnprintf(full_url, urllen, "%s0200", url);
        easy_setopt(easy[num_handles], CURLOPT_HTTPAUTH, CURLAUTH_NTLM);
      }
      else {
        msnprintf(full_url, urllen, "%s0100", url);
        easy_setopt(easy[num_handles], CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
      }
      easy_setopt(easy[num_handles], CURLOPT_FRESH_CONNECT, 1L);
      easy_setopt(easy[num_handles], CURLOPT_URL, full_url);
      easy_setopt(easy[num_handles], CURLOPT_VERBOSE, 1L);
      easy_setopt(easy[num_handles], CURLOPT_HTTPGET, 1L);
      easy_setopt(easy[num_handles], CURLOPT_USERPWD, "testuser:testpass");
      easy_setopt(easy[num_handles], CURLOPT_WRITEFUNCTION, callback);
      easy_setopt(easy[num_handles], CURLOPT_WRITEDATA, easy + num_handles);
      easy_setopt(easy[num_handles], CURLOPT_HEADER, 1L);

      multi_add_handle(multi, easy[num_handles]);
      num_handles += 1;
      state = NeedSocketForNewHandle;
    }

    multi_perform(multi, &running);

    fprintf(stderr, "%s:%d running %d state %d\n",
            __FILE__, __LINE__, running, state);

    abort_on_test_timeout();

    if(!running && state == NoMoreHandles)
      break; /* done */

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    multi_fdset(multi, &fdread, &fdwrite, &fdexcep, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    if(state == NeedSocketForNewHandle) {
      if(maxfd != -1 && !found_new_socket) {
        fprintf(stderr, "Warning: socket did not open immediately for new "
                "handle (trying again)\n");
        continue;
      }
      state = num_handles < MAX_EASY_HANDLES ? ReadyForNewHandle
                                             : NoMoreHandles;
      fprintf(stderr, "%s:%d new state %d\n",
              __FILE__, __LINE__, state);
    }

    multi_timeout(multi, &timeout);

    /* At this point, timeout is guaranteed to be greater or equal than -1. */

    fprintf(stderr, "%s:%d num_handles %d timeout %ld running %d\n",
            __FILE__, __LINE__, num_handles, timeout, running);

    if(timeout != -1L) {
      int itimeout = (timeout > (long)INT_MAX) ? INT_MAX : (int)timeout;
      interval.tv_sec = itimeout/1000;
      interval.tv_usec = (itimeout%1000)*1000;
    }
    else {
      interval.tv_sec = 0;
      interval.tv_usec = 5000;

      /* if there's no timeout and we get here on the last handle, we may
         already have read the last part of the stream so waiting makes no
         sense */
      if(!running && num_handles == MAX_EASY_HANDLES) {
        break;
      }
    }

    select_test(maxfd + 1, &fdread, &fdwrite, &fdexcep, &interval);

    abort_on_test_timeout();
  }

test_cleanup:

  /* proper cleanup sequence - type PB */

  for(i = 0; i < MAX_EASY_HANDLES; i++) {
    printf("Data connection %d: %d\n", i, counter[i]);
    curl_multi_remove_handle(multi, easy[i]);
    curl_easy_cleanup(easy[i]);
  }

  curl_multi_cleanup(multi);
  curl_global_cleanup();

  free(full_url);

  return res;
}