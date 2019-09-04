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
typedef  int /*<<< orphan*/  CURLM ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLMOPT_MAX_HOST_CONNECTIONS ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_perform (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multi_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int test(char *URL)
{
  CURLM *curlm = NULL;
  CURL *curl1 = NULL;
  CURL *curl2 = NULL;
  int running_handles = 0;
  int res = 0;

  global_init(CURL_GLOBAL_ALL);

  multi_init(curlm);
  multi_setopt(curlm, CURLMOPT_MAX_HOST_CONNECTIONS, 1);

  easy_init(curl1);
  easy_setopt(curl1, CURLOPT_URL, URL);
  multi_add_handle(curlm, curl1);

  easy_init(curl2);
  easy_setopt(curl2, CURLOPT_URL, URL);
  multi_add_handle(curlm, curl2);

  multi_perform(curlm, &running_handles);

  multi_remove_handle(curlm, curl2);
  curl_easy_cleanup(curl2);

  /* If curl2 is still in the connect-pending list, this will crash */
  multi_remove_handle(curlm, curl1);
  curl_easy_cleanup(curl1);

test_cleanup:
  curl_multi_cleanup(curlm);
  curl_global_cleanup();
  return res;
}