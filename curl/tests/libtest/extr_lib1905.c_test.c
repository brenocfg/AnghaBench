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
struct timeval {long tv_sec; long tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  char CURLSH ;
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_COOKIEFILE ; 
 int /*<<< orphan*/  CURLOPT_COOKIEJAR ; 
 int /*<<< orphan*/  CURLOPT_COOKIELIST ; 
 int /*<<< orphan*/  CURLOPT_SHARE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLSHOPT_SHARE ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_COOKIE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_fdset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * curl_multi_init () ; 
 int /*<<< orphan*/  curl_multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_timeout (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  curl_share_cleanup (char*) ; 
 char* curl_share_init () ; 
 int /*<<< orphan*/  curl_share_setopt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

int test(char *URL)
{
  CURLSH *sh = NULL;
  CURL *ch = NULL;
  int unfinished;

  CURLM *cm = curl_multi_init();
  if(!cm)
    return 1;
  sh = curl_share_init();
  if(!sh)
    goto cleanup;

  curl_share_setopt(sh, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
  curl_share_setopt(sh, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);

  ch = curl_easy_init();
  if(!ch)
    goto cleanup;

  curl_easy_setopt(ch, CURLOPT_SHARE, sh);
  curl_easy_setopt(ch, CURLOPT_URL, URL);
  curl_easy_setopt(ch, CURLOPT_COOKIEFILE, "log/cookies1905");
  curl_easy_setopt(ch, CURLOPT_COOKIEJAR, "log/cookies1905");

  curl_multi_add_handle(cm, ch);

  unfinished = 1;
  while(unfinished) {
    int MAX = 0;
    long max_tout;
    fd_set R, W, E;
    struct timeval timeout;

    FD_ZERO(&R);
    FD_ZERO(&W);
    FD_ZERO(&E);
    curl_multi_perform(cm, &unfinished);

    curl_multi_fdset(cm, &R, &W, &E, &MAX);
    curl_multi_timeout(cm, &max_tout);

    if(max_tout > 0) {
      timeout.tv_sec = max_tout / 1000;
      timeout.tv_usec = (max_tout % 1000) * 1000;
    }
    else {
      timeout.tv_sec = 0;
      timeout.tv_usec = 1000;
    }

    select(MAX + 1, &R, &W, &E, &timeout);
  }

  curl_easy_setopt(ch, CURLOPT_COOKIELIST, "FLUSH");
  curl_easy_setopt(ch, CURLOPT_SHARE, NULL);

  curl_multi_remove_handle(cm, ch);
  cleanup:
  curl_easy_cleanup(ch);
  curl_share_cleanup(sh);
  curl_multi_cleanup(cm);
  curl_global_cleanup();

  return 0;
}