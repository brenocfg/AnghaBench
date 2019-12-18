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
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLINFO_PROTOCOL ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long*) ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 char* curl_easy_strerror (int) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,long) ; 
 int /*<<< orphan*/  stderr ; 

int test(char *URL)
{
  CURLcode res = 0;
  CURL *curl = NULL;
  long protocol = 0;

  global_init(CURL_GLOBAL_ALL);
  easy_init(curl);

  easy_setopt(curl, CURLOPT_URL, URL);
  res = curl_easy_perform(curl);
  if(res) {
    fprintf(stderr, "curl_easy_perform() returned %d (%s)\n",
            res, curl_easy_strerror(res));
    goto test_cleanup;
  }

  res = curl_easy_getinfo(curl, CURLINFO_PROTOCOL, &protocol);
  if(res) {
    fprintf(stderr, "curl_easy_getinfo() returned %d (%s)\n",
            res, curl_easy_strerror(res));
    goto test_cleanup;
  }

  printf("Protocol: %x\n", protocol);

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return 0;

test_cleanup:

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res; /* return the final return code */
}