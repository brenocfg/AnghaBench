#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * cookielist; } ;
struct TYPE_4__ {scalar_t__* str; } ;
struct Curl_easy {int /*<<< orphan*/ * cookies; TYPE_3__* share; TYPE_2__ change; TYPE_1__ set; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cookies; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_LOCK_ACCESS_SINGLE ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_COOKIE ; 
 int /*<<< orphan*/  Curl_cookie_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_cookie_loadfiles (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_share_lock (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_share_unlock (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 size_t STRING_COOKIEJAR ; 
 scalar_t__ cookie_output (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,scalar_t__) ; 

void Curl_flush_cookies(struct Curl_easy *data, bool cleanup)
{
  if(data->set.str[STRING_COOKIEJAR]) {
    if(data->change.cookielist) {
      /* If there is a list of cookie files to read, do it first so that
         we have all the told files read before we write the new jar.
         Curl_cookie_loadfiles() LOCKS and UNLOCKS the share itself! */
      Curl_cookie_loadfiles(data);
    }

    Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);

    /* if we have a destination file for all the cookies to get dumped to */
    if(cookie_output(data->cookies, data->set.str[STRING_COOKIEJAR]))
      infof(data, "WARNING: failed to save cookies in %s\n",
            data->set.str[STRING_COOKIEJAR]);
  }
  else {
    if(cleanup && data->change.cookielist) {
      /* since nothing is written, we can just free the list of cookie file
         names */
      curl_slist_free_all(data->change.cookielist); /* clean up list */
      data->change.cookielist = NULL;
    }
    Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
  }

  if(cleanup && (!data->share || (data->cookies != data->share->cookies))) {
    Curl_cookie_cleanup(data->cookies);
    data->cookies = NULL;
  }
  Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
}