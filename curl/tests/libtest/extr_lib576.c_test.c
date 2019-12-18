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
typedef  char chunk_data_t ;
typedef  int CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURLE_OK ; 
 int CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLOPT_CHUNK_BGN_FUNCTION ; 
 int /*<<< orphan*/  CURLOPT_CHUNK_DATA ; 
 int /*<<< orphan*/  CURLOPT_CHUNK_END_FUNCTION ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WILDCARDMATCH ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 char* chunk_bgn ; 
 char* chunk_end ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

int test(char *URL)
{
  CURL *handle = NULL;
  CURLcode res = CURLE_OK;
  chunk_data_t chunk_data = {0, 0};
  curl_global_init(CURL_GLOBAL_ALL);
  handle = curl_easy_init();
  if(!handle) {
    res = CURLE_OUT_OF_MEMORY;
    goto test_cleanup;
  }

  test_setopt(handle, CURLOPT_URL, URL);
  test_setopt(handle, CURLOPT_WILDCARDMATCH, 1L);
  test_setopt(handle, CURLOPT_CHUNK_BGN_FUNCTION, chunk_bgn);
  test_setopt(handle, CURLOPT_CHUNK_END_FUNCTION, chunk_end);
  test_setopt(handle, CURLOPT_CHUNK_DATA, &chunk_data);

  res = curl_easy_perform(handle);

test_cleanup:
  if(handle)
    curl_easy_cleanup(handle);
  curl_global_cleanup();
  return res;
}