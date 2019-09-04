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
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_duphandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 

int test(char *URL)
{
  CURLcode code;
  int rc = 99;

  code = curl_global_init(CURL_GLOBAL_ALL);
  if(code == CURLE_OK) {
    CURL *curl = curl_easy_init();
    if(curl) {
      CURL *curl2;

      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

      curl2 = curl_easy_duphandle(curl);
      if(curl2) {

        code = curl_easy_setopt(curl2, CURLOPT_URL, URL);
        if(code == CURLE_OK) {

          code = curl_easy_perform(curl2);
          if(code == CURLE_OK)
            rc = 0;
          else
            rc = 1;
        }
        else
          rc = 2;

        curl_easy_cleanup(curl2);
      }
      else
        rc = 3;

      curl_easy_cleanup(curl);
    }
    else
      rc = 4;

    curl_global_cleanup();
  }
  else
    rc = 5;

  return rc;
}