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
typedef  int CURLcode ;
typedef  scalar_t__ CURLUcode ;
typedef  int /*<<< orphan*/  CURLU ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_CURLU ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLUPART_URL ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 char* curl_easy_strerror (int) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/ * curl_url () ; 
 int /*<<< orphan*/  curl_url_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_url_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int test(char *URL)
{
  CURL *handle = NULL;
  CURLcode res = 0;
  CURLU *urlp = NULL;
  CURLUcode uc = 0;

  global_init(CURL_GLOBAL_ALL);
  easy_init(handle);

  urlp = curl_url();

  if(!urlp) {
    fprintf(stderr, "problem init URL api.");
    goto test_cleanup;
  }

  uc = curl_url_set(urlp, CURLUPART_URL, URL, 0);
  if(uc) {
    fprintf(stderr, "problem setting CURLUPART_URL.");
    goto test_cleanup;
  }

  /* demonstrate override behavior */
  easy_setopt(handle, CURLOPT_URL, "http://www.example.com");

  easy_setopt(handle, CURLOPT_CURLU, urlp);
  easy_setopt(handle, CURLOPT_VERBOSE, 1L);

  res = curl_easy_perform(handle);

  if(res) {
    fprintf(stderr, "%s:%d curl_easy_perform() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }

test_cleanup:

  curl_url_cleanup(urlp);
  curl_easy_cleanup(handle);
  curl_global_cleanup();

  return res;
}