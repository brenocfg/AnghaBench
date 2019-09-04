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
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLINFO_NUM_CONNECTS ; 
 int TEST_ERR_FAILURE ; 
 int TEST_ERR_MAJOR_BAD ; 
 int TEST_ERR_SUCCESS ; 
 scalar_t__ curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long*) ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int perform_and_check_connections(CURL *curl, const char *description,
                                         long expected_connections)
{
  CURLcode res;
  long connections = 0;

  res = curl_easy_perform(curl);
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  res = curl_easy_getinfo(curl, CURLINFO_NUM_CONNECTS, &connections);
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_getinfo() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  fprintf(stderr, "%s: expected: %ld connections; actual: %ld connections\n",
          description, expected_connections, connections);

  if(connections != expected_connections) {
    return TEST_ERR_FAILURE;
  }

  return TEST_ERR_SUCCESS;
}