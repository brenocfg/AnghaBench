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
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_HEADERFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_PROXY ; 
 int /*<<< orphan*/  CURLOPT_PROXYUSERPWD ; 
 int /*<<< orphan*/  CURLOPT_USERAGENT ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 char* SYNCTIME_UA ; 
 char** SyncTime_CURL_WriteHeader ; 
 char** SyncTime_CURL_WriteOutput ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 

void SyncTime_CURL_Init(CURL *curl, char *proxy_port,
                        char *proxy_user_password)
{
  if(strlen(proxy_port) > 0)
    curl_easy_setopt(curl, CURLOPT_PROXY, proxy_port);

  if(strlen(proxy_user_password) > 0)
    curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, proxy_user_password);

#ifdef SYNCTIME_UA
  curl_easy_setopt(curl, CURLOPT_USERAGENT, SYNCTIME_UA);
#endif
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, *SyncTime_CURL_WriteOutput);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, *SyncTime_CURL_WriteHeader);
}