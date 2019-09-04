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
 int CURLE_FAILED_INIT ; 
 int CURLE_HTTP_RETURNED_ERROR ; 
 int CURLE_OK ; 
 int /*<<< orphan*/  CURLINFO_SCHEME ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_duphandle (int /*<<< orphan*/ *) ; 
 int curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_reset (int /*<<< orphan*/ *) ; 
 char* curl_easy_strerror (int) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int test(char *URL)
{
  CURL *curl, *dupe = NULL;
  char *scheme;
  int res = CURLE_OK;

  global_init(CURL_GLOBAL_ALL);

  easy_init(curl);

  /* Test that scheme is properly initialized on curl_easy_init.
  */

  res = curl_easy_getinfo(curl, CURLINFO_SCHEME, &scheme);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }
  if(scheme != NULL) {
    fprintf(stderr, "%s:%d scheme init failed; expected NULL\n",
            __FILE__, __LINE__);
    res = CURLE_FAILED_INIT;
    goto test_cleanup;
  }

  easy_setopt(curl, CURLOPT_URL, URL);

  res = curl_easy_perform(curl);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_perform() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }

  /* Test that a scheme is properly set after receiving an HTTP resource.
  */

  res = curl_easy_getinfo(curl, CURLINFO_SCHEME, &scheme);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }
  if(memcmp(scheme, "HTTP", 5) != 0) {
    fprintf(stderr, "%s:%d scheme of http resource is incorrect; "
            "expected 'HTTP' but is %s\n",
            __FILE__, __LINE__,
            (scheme == NULL ? "NULL" : "invalid"));
    res = CURLE_HTTP_RETURNED_ERROR;
    goto test_cleanup;
  }

  /* Test that a scheme is properly initialized on curl_easy_duphandle.
  */

  dupe = curl_easy_duphandle(curl);
  if(!dupe) {
    fprintf(stderr, "%s:%d curl_easy_duphandle() failed\n",
            __FILE__, __LINE__);
    res = CURLE_FAILED_INIT;
    goto test_cleanup;
  }

  res = curl_easy_getinfo(dupe, CURLINFO_SCHEME, &scheme);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }
  if(scheme != 0) {
    fprintf(stderr, "%s:%d scheme init failed; expected NULL\n",
            __FILE__, __LINE__);
    res = CURLE_FAILED_INIT;
    goto test_cleanup;
  }


  /* Test that a scheme is properly initialized on curl_easy_reset.
  */

  curl_easy_reset(curl);

  res = curl_easy_getinfo(curl, CURLINFO_SCHEME, &scheme);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }
  if(scheme != 0) {
    fprintf(stderr, "%s:%d scheme init failed; expected NULL\n",
            __FILE__, __LINE__);
    res = CURLE_FAILED_INIT;
    goto test_cleanup;
  }

test_cleanup:
  curl_easy_cleanup(curl);
  curl_easy_cleanup(dupe);
  curl_global_cleanup();
  return res;
}