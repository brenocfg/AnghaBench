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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int NUM_HANDLES ; 
 int /*<<< orphan*/  abort_on_test_timeout () ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_fdset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  select_test (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  start_test_timing () ; 
 int /*<<< orphan*/  stderr ; 

int test(char *URL)
{
  int res = 0;
  CURL *curl[NUM_HANDLES];
  int running;
  CURLM *m = NULL;
  int current = 0;
  int i;

  for(i = 0; i < NUM_HANDLES; i++)
    curl[i] = NULL;

  start_test_timing();

  global_init(CURL_GLOBAL_ALL);

  /* get NUM_HANDLES easy handles */
  for(i = 0; i < NUM_HANDLES; i++) {
    easy_init(curl[i]);
    /* specify target */
    easy_setopt(curl[i], CURLOPT_URL, URL);
    /* go verbose */
    easy_setopt(curl[i], CURLOPT_VERBOSE, 1L);
  }

  multi_init(m);

  multi_add_handle(m, curl[current]);

  fprintf(stderr, "Start at URL 0\n");

  for(;;) {
    struct timeval interval;
    fd_set rd, wr, exc;
    int maxfd = -99;

    interval.tv_sec = 1;
    interval.tv_usec = 0;

    multi_perform(m, &running);

    abort_on_test_timeout();

    if(!running) {
#ifdef LIB527
      /* NOTE: this code does not remove the handle from the multi handle
         here, which would be the nice, sane and documented way of working.
         This however tests that the API survives this abuse gracefully. */
      curl_easy_cleanup(curl[current]);
      curl[current] = NULL;
#endif
      if(++current < NUM_HANDLES) {
        fprintf(stderr, "Advancing to URL %d\n", current);
#ifdef LIB532
        /* first remove the only handle we use */
        curl_multi_remove_handle(m, curl[0]);

        /* make us re-use the same handle all the time, and try resetting
           the handle first too */
        curl_easy_reset(curl[0]);
        easy_setopt(curl[0], CURLOPT_URL, URL);
        /* go verbose */
        easy_setopt(curl[0], CURLOPT_VERBOSE, 1L);

        /* re-add it */
        multi_add_handle(m, curl[0]);
#else
        multi_add_handle(m, curl[current]);
#endif
      }
      else {
        break; /* done */
      }
    }

    FD_ZERO(&rd);
    FD_ZERO(&wr);
    FD_ZERO(&exc);

    multi_fdset(m, &rd, &wr, &exc, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    select_test(maxfd + 1, &rd, &wr, &exc, &interval);

    abort_on_test_timeout();
  }

test_cleanup:

#if defined(LIB526)

  /* test 526 and 528 */
  /* proper cleanup sequence - type PB */

  for(i = 0; i < NUM_HANDLES; i++) {
    curl_multi_remove_handle(m, curl[i]);
    curl_easy_cleanup(curl[i]);
  }
  curl_multi_cleanup(m);
  curl_global_cleanup();

#elif defined(LIB527)

  /* test 527 */

  /* Upon non-failure test flow the easy's have already been cleanup'ed. In
     case there is a failure we arrive here with easy's that have not been
     cleanup'ed yet, in this case we have to cleanup them or otherwise these
     will be leaked, let's use undocumented cleanup sequence - type UB */

  if(res)
    for(i = 0; i < NUM_HANDLES; i++)
      curl_easy_cleanup(curl[i]);

  curl_multi_cleanup(m);
  curl_global_cleanup();

#elif defined(LIB532)

  /* test 532 */
  /* undocumented cleanup sequence - type UB */

  for(i = 0; i < NUM_HANDLES; i++)
    curl_easy_cleanup(curl[i]);
  curl_multi_cleanup(m);
  curl_global_cleanup();

#endif

  return res;
}