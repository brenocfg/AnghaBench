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
struct timeval {int tv_sec; long tv_usec; } ;
struct curl_slist {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_MAIL_FROM ; 
 int /*<<< orphan*/  CURLOPT_MAIL_RCPT ; 
 int /*<<< orphan*/  CURLOPT_PASSWORD ; 
 int /*<<< orphan*/  CURLOPT_READFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_USERNAME ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_DEFAULT ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 long MAILFROM ; 
 scalar_t__ MULTI_PERFORM_HANG_TIMEOUT ; 
 long PASSWORD ; 
 int /*<<< orphan*/  RECIPIENT ; 
 long USERNAME ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_fdset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  curl_multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_timeout (int /*<<< orphan*/ *,long*) ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 long read_callback ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ tutil_tvdiff (struct timeval,struct timeval) ; 
 struct timeval tutil_tvnow () ; 

int test(char *URL)
{
   int res = 0;
   CURL *curl = NULL;
   CURLM *mcurl = NULL;
   int still_running = 1;
   struct timeval mp_start;
   struct curl_slist *rcpt_list = NULL;

   curl_global_init(CURL_GLOBAL_DEFAULT);

   easy_init(curl);

   multi_init(mcurl);

   rcpt_list = curl_slist_append(rcpt_list, RECIPIENT);
   /* more addresses can be added here
      rcpt_list = curl_slist_append(rcpt_list, "<others@example.com>");
   */

   curl_easy_setopt(curl, CURLOPT_URL, URL);
#if 0
   curl_easy_setopt(curl, CURLOPT_USERNAME, USERNAME);
   curl_easy_setopt(curl, CURLOPT_PASSWORD, PASSWORD);
#endif
   curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
   curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
   curl_easy_setopt(curl, CURLOPT_MAIL_FROM, MAILFROM);
   curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, rcpt_list);
   curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
   multi_add_handle(mcurl, curl);

   mp_start = tutil_tvnow();

  /* we start some action by calling perform right away */
  curl_multi_perform(mcurl, &still_running);

  while(still_running) {
    struct timeval timeout;
    int rc; /* select() return code */

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

    curl_multi_timeout(mcurl, &curl_timeo);
    if(curl_timeo >= 0) {
      timeout.tv_sec = curl_timeo / 1000;
      if(timeout.tv_sec > 1)
        timeout.tv_sec = 1;
      else
        timeout.tv_usec = (curl_timeo % 1000) * 1000;
    }

    /* get file descriptors from the transfers */
    curl_multi_fdset(mcurl, &fdread, &fdwrite, &fdexcep, &maxfd);

    /* In a real-world program you OF COURSE check the return code of the
       function calls.  On success, the value of maxfd is guaranteed to be
       greater or equal than -1.  We call select(maxfd + 1, ...), specially in
       case of (maxfd == -1), we call select(0, ...), which is basically equal
       to sleep. */

    rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);

    if(tutil_tvdiff(tutil_tvnow(), mp_start) > MULTI_PERFORM_HANG_TIMEOUT) {
      fprintf(stderr, "ABORTING TEST, since it seems "
              "that it would have run forever.\n");
      break;
    }

    switch(rc) {
    case -1:
      /* select error */
      break;
    case 0: /* timeout */
    default: /* action */
      curl_multi_perform(mcurl, &still_running);
      break;
    }
  }

test_cleanup:

  curl_slist_free_all(rcpt_list);
  curl_multi_remove_handle(mcurl, curl);
  curl_multi_cleanup(mcurl);
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}