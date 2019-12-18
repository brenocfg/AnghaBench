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
typedef  char curl_slist ;
struct Tdata {char* url; char* share; } ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_COOKIEFILE ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  CURLOPT_SHARE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  curl_slist_free_all (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* sethost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void *fire(void *ptr)
{
  CURLcode code;
  struct curl_slist *headers;
  struct Tdata *tdata = (struct Tdata*)ptr;
  CURL *curl;

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    return NULL;
  }

  headers = sethost(NULL);
  curl_easy_setopt(curl, CURLOPT_VERBOSE,    1L);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_URL,        tdata->url);
  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
  printf("CURLOPT_SHARE\n");
  curl_easy_setopt(curl, CURLOPT_SHARE, tdata->share);

  printf("PERFORM\n");
  code = curl_easy_perform(curl);
  if(code) {
    int i = 0;
    fprintf(stderr, "perform url '%s' repeat %d failed, curlcode %d\n",
            tdata->url, i, (int)code);
  }

  printf("CLEANUP\n");
  curl_easy_cleanup(curl);
  curl_slist_free_all(headers);

  return NULL;
}