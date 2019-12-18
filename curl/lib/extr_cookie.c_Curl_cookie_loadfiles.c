#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct curl_slist {struct curl_slist* next; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {struct curl_slist* cookielist; } ;
struct TYPE_3__ {int /*<<< orphan*/  cookiesession; } ;
struct Curl_easy {TYPE_2__ change; struct CookieInfo* cookies; TYPE_1__ set; } ;
struct CookieInfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_LOCK_ACCESS_SINGLE ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_COOKIE ; 
 struct CookieInfo* Curl_cookie_init (struct Curl_easy*,int /*<<< orphan*/ ,struct CookieInfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_share_lock (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_share_unlock (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int /*<<< orphan*/ ) ; 

void Curl_cookie_loadfiles(struct Curl_easy *data)
{
  struct curl_slist *list = data->change.cookielist;
  if(list) {
    Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
    while(list) {
      struct CookieInfo *newcookies = Curl_cookie_init(data,
                                        list->data,
                                        data->cookies,
                                        data->set.cookiesession);
      if(!newcookies)
        /* Failure may be due to OOM or a bad cookie; both are ignored
         * but only the first should be
         */
        infof(data, "ignoring failed cookie_init for %s\n", list->data);
      else
        data->cookies = newcookies;
      list = list->next;
    }
    curl_slist_free_all(data->change.cookielist); /* clean up list */
    data->change.cookielist = NULL; /* don't do this again! */
    Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
  }
}