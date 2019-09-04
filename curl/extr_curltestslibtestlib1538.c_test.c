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
typedef  scalar_t__ CURLcode ;
typedef  scalar_t__ CURLSHcode ;
typedef  scalar_t__ CURLMcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLM_CALL_MULTI_PERFORM ; 
 scalar_t__ CURLM_LAST ; 
 scalar_t__ CURLSHE_LAST ; 
 scalar_t__ CURLSHE_OK ; 
 scalar_t__ CURL_LAST ; 
 scalar_t__ INT_MAX ; 
 char* curl_easy_strerror (scalar_t__) ; 
 char* curl_multi_strerror (scalar_t__) ; 
 char* curl_share_strerror (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 

int test(char *URL)
{
  int res = 0;
  CURLcode easyret;
  CURLMcode multiret;
  CURLSHcode shareret;
  (void)URL;

  curl_easy_strerror(INT_MAX);
  curl_multi_strerror(INT_MAX);
  curl_share_strerror(INT_MAX);
  curl_easy_strerror(-INT_MAX);
  curl_multi_strerror(-INT_MAX);
  curl_share_strerror(-INT_MAX);
  for(easyret = CURLE_OK; easyret <= CURL_LAST; easyret++) {
    printf("e%d: %s\n", (int)easyret, curl_easy_strerror(easyret));
  }
  for(multiret = CURLM_CALL_MULTI_PERFORM; multiret <= CURLM_LAST;
      multiret++) {
    printf("m%d: %s\n", (int)multiret, curl_multi_strerror(multiret));
  }
  for(shareret = CURLSHE_OK; shareret <= CURLSHE_LAST; shareret++) {
    printf("s%d: %s\n", (int)shareret, curl_share_strerror(shareret));
  }

  return (int)res;
}