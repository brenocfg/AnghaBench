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
struct curl_slist {int dummy; } ;
struct GlobalConfig {scalar_t__ libcurl; } ;
typedef  int /*<<< orphan*/  CURLoption ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CODE2 (char*,char const*,int) ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct curl_slist*) ; 
 int /*<<< orphan*/  libcurl_generate_slist (struct curl_slist*,int*) ; 

CURLcode tool_setopt_slist(CURL *curl, struct GlobalConfig *config,
                           const char *name, CURLoption tag,
                           struct curl_slist *list)
{
  CURLcode ret = CURLE_OK;

  ret = curl_easy_setopt(curl, tag, list);

  if(config->libcurl && list && !ret) {
    int i;

    ret = libcurl_generate_slist(list, &i);
    if(!ret)
      CODE2("curl_easy_setopt(hnd, %s, slist%d);", name, i);
  }

 nomem:
  return ret;
}