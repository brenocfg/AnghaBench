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
 int /*<<< orphan*/  CURLINFO_CONDITION_UNMET ; 
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_TIMECONDITION ; 
 int /*<<< orphan*/  CURLOPT_TIMEVALUE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 scalar_t__ CURL_TIMECOND_IFMODSINCE ; 
 int TEST_ERR_FAILURE ; 
 int TEST_ERR_SUCCESS ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long*) ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 

int test(char *URL)
{
  long unmet;
  CURL *curl = NULL;
  int res = 0;

  global_init(CURL_GLOBAL_ALL);

  easy_init(curl);

  easy_setopt(curl, CURLOPT_URL, URL);
  easy_setopt(curl, CURLOPT_HEADER, 1L);
  easy_setopt(curl, CURLOPT_TIMECONDITION, (long)CURL_TIMECOND_IFMODSINCE);

  /* TIMEVALUE in the future */
  easy_setopt(curl, CURLOPT_TIMEVALUE, 1566210680L);

  res = curl_easy_perform(curl);
  if(res)
    goto test_cleanup;

  curl_easy_getinfo(curl, CURLINFO_CONDITION_UNMET, &unmet);
  if(unmet != 1L) {
    res = TEST_ERR_FAILURE; /* not correct */
    goto test_cleanup;
  }

  /* TIMEVALUE in the past */
  easy_setopt(curl, CURLOPT_TIMEVALUE, 1L);

  res = curl_easy_perform(curl);
  if(res)
    goto test_cleanup;

  curl_easy_getinfo(curl, CURLINFO_CONDITION_UNMET, &unmet);
  if(unmet != 0L) {
    res = TEST_ERR_FAILURE; /* not correct */
    goto test_cleanup;
  }

  res = TEST_ERR_SUCCESS; /* this is where we should be */

test_cleanup:

  /* always cleanup */
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}