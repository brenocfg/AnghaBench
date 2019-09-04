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

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_NOPROGRESS ; 
 int /*<<< orphan*/  CURLOPT_NOSIGNAL ; 
 int /*<<< orphan*/  CURLOPT_PROGRESSDATA ; 
 int /*<<< orphan*/  CURLOPT_PROGRESSFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_TIMEOUT ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ ) ; 
 int curl_easy_perform (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 long progressCallback ; 

int test(char *URL)
{
  int res = 0;

  global_init(CURL_GLOBAL_ALL);

  easy_init(curl);

  easy_setopt(curl, CURLOPT_URL, URL);
  easy_setopt(curl, CURLOPT_TIMEOUT, (long)7);
  easy_setopt(curl, CURLOPT_NOSIGNAL, (long)1);
  easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progressCallback);
  easy_setopt(curl, CURLOPT_PROGRESSDATA, NULL);
  easy_setopt(curl, CURLOPT_NOPROGRESS, (long)0);

  res = curl_easy_perform(curl);

test_cleanup:

  /* undocumented cleanup sequence - type UA */

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}