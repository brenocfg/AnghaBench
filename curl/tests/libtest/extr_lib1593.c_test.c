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
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLINFO_CONDITION_UNMET ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  CURLOPT_TIMECONDITION ; 
 int /*<<< orphan*/  CURLOPT_TIMEVALUE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 scalar_t__ CURL_TIMECOND_IFMODSINCE ; 
 int TEST_ERR_FAILURE ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long*) ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 char* curl_slist_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (char*) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 

int test(char *URL)
{
  struct curl_slist *header = NULL;
  long unmet;
  CURL *curl = NULL;
  int res = 0;

  global_init(CURL_GLOBAL_ALL);

  easy_init(curl);

  easy_setopt(curl, CURLOPT_URL, URL);
  easy_setopt(curl, CURLOPT_TIMECONDITION, (long)CURL_TIMECOND_IFMODSINCE);
  /* Some TIMEVALUE; it doesn't matter. */
  easy_setopt(curl, CURLOPT_TIMEVALUE, 1566210680L);

  header = curl_slist_append(NULL, "If-Modified-Since:");
  if(!header) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }

  easy_setopt(curl, CURLOPT_HTTPHEADER, header);

  res = curl_easy_perform(curl);
  if(res)
    goto test_cleanup;

  /* Confirm that the condition checking still worked, even though we
   * suppressed the actual header.
   * The server returns 304, which means the condition is "unmet".
   */

  res = curl_easy_getinfo(curl, CURLINFO_CONDITION_UNMET, &unmet);
  if(res)
    goto test_cleanup;

  if(unmet != 1L) {
    res = TEST_ERR_FAILURE;
    goto test_cleanup;
  }

test_cleanup:

  /* always cleanup */
  curl_easy_cleanup(curl);
  curl_slist_free_all(header);
  curl_global_cleanup();

  return res;
}