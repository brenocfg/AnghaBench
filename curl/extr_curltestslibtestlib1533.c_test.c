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
struct cb_data {scalar_t__ remaining_bytes; } ;
typedef  long curl_off_t ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_FAILED_INIT ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_KEEP_SENDING_ON_ERROR ; 
 int /*<<< orphan*/  CURLOPT_POST ; 
 int /*<<< orphan*/  CURLOPT_POSTFIELDSIZE_LARGE ; 
 int /*<<< orphan*/  CURLOPT_READDATA ; 
 int /*<<< orphan*/  CURLOPT_READFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int TEST_ERR_MAJOR_BAD ; 
 scalar_t__ TEST_ERR_SUCCESS ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ perform_and_check_connections (int /*<<< orphan*/ *,char*,int) ; 
 long read_callback ; 
 int /*<<< orphan*/  reset_data (struct cb_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 long write_callback ; 

int test(char *URL)
{
  struct cb_data data;
  CURL *curl = NULL;
  CURLcode res = CURLE_FAILED_INIT;

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  curl = curl_easy_init();
  if(curl == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  reset_data(&data, curl);

  test_setopt(curl, CURLOPT_URL, URL);
  test_setopt(curl, CURLOPT_POST, 1L);
  test_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE,
              (curl_off_t)data.remaining_bytes);
  test_setopt(curl, CURLOPT_VERBOSE, 1L);
  test_setopt(curl, CURLOPT_READFUNCTION, read_callback);
  test_setopt(curl, CURLOPT_READDATA, &data);
  test_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  test_setopt(curl, CURLOPT_WRITEDATA, &data);

  res = perform_and_check_connections(curl,
    "First request without CURLOPT_KEEP_SENDING_ON_ERROR", 1);
  if(res != TEST_ERR_SUCCESS) {
    goto test_cleanup;
  }

  reset_data(&data, curl);

  res = perform_and_check_connections(curl,
    "Second request without CURLOPT_KEEP_SENDING_ON_ERROR", 1);
  if(res != TEST_ERR_SUCCESS) {
    goto test_cleanup;
  }

  test_setopt(curl, CURLOPT_KEEP_SENDING_ON_ERROR, 1L);

  reset_data(&data, curl);

  res = perform_and_check_connections(curl,
    "First request with CURLOPT_KEEP_SENDING_ON_ERROR", 1);
  if(res != TEST_ERR_SUCCESS) {
    goto test_cleanup;
  }

  reset_data(&data, curl);

  res = perform_and_check_connections(curl,
    "Second request with CURLOPT_KEEP_SENDING_ON_ERROR", 0);
  if(res != TEST_ERR_SUCCESS) {
    goto test_cleanup;
  }

  res = TEST_ERR_SUCCESS;

test_cleanup:

  curl_easy_cleanup(curl);

  curl_global_cleanup();

  return (int)res;
}