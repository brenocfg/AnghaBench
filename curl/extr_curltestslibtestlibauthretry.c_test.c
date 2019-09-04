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
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 long CURLAUTH_NONE ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  libtest_arg2 ; 
 int /*<<< orphan*/  libtest_arg3 ; 
 long parse_auth_name (int /*<<< orphan*/ ) ; 
 scalar_t__ send_right_password (int /*<<< orphan*/ *,char*,int,long) ; 
 scalar_t__ send_wrong_password (int /*<<< orphan*/ *,char*,int,long) ; 
 int /*<<< orphan*/  stderr ; 

int test(char *url)
{
  CURLcode res;
  CURL *curl = NULL;

  long main_auth_scheme = parse_auth_name(libtest_arg2);
  long fallback_auth_scheme = parse_auth_name(libtest_arg3);

  if(main_auth_scheme == CURLAUTH_NONE ||
      fallback_auth_scheme == CURLAUTH_NONE) {
    fprintf(stderr, "auth schemes not found on commandline\n");
    return TEST_ERR_MAJOR_BAD;
  }

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  /* Send wrong password, then right password */

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  res = send_wrong_password(curl, url, 100, main_auth_scheme);
  if(res != CURLE_OK)
    goto test_cleanup;

  res = send_right_password(curl, url, 200, fallback_auth_scheme);
  if(res != CURLE_OK)
    goto test_cleanup;

  curl_easy_cleanup(curl);

  /* Send wrong password twice, then right password */
  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  res = send_wrong_password(curl, url, 300, main_auth_scheme);
  if(res != CURLE_OK)
    goto test_cleanup;

  res = send_wrong_password(curl, url, 400, fallback_auth_scheme);
  if(res != CURLE_OK)
    goto test_cleanup;

  res = send_right_password(curl, url, 500, fallback_auth_scheme);
  if(res != CURLE_OK)
    goto test_cleanup;

test_cleanup:

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}