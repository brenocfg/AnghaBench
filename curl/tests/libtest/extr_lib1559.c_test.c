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
 int /*<<< orphan*/  CURLOPT_POSTFIELDS ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLUPART_SCHEME ; 
 int /*<<< orphan*/  CURLUPART_URL ; 
 int /*<<< orphan*/  CURLUPART_USER ; 
 int /*<<< orphan*/  CURLU_NON_SUPPORT_SCHEME ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int EXCESSIVE ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/ * curl_url () ; 
 int /*<<< orphan*/  curl_url_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_url_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

int test(char *URL)
{
  CURLcode res = 0;
  CURL *curl = NULL;
  char *longurl = malloc(EXCESSIVE);
  CURLU *u;
  (void)URL;

  memset(longurl, 'a', EXCESSIVE);
  longurl[EXCESSIVE-1] = 0;

  global_init(CURL_GLOBAL_ALL);
  easy_init(curl);

  res = curl_easy_setopt(curl, CURLOPT_URL, longurl);
  printf("CURLOPT_URL %d bytes URL == %d\n",
         EXCESSIVE, (int)res);

  res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, longurl);
  printf("CURLOPT_POSTFIELDS %d bytes data == %d\n",
         EXCESSIVE, (int)res);

  u = curl_url();
  if(u) {
    CURLUcode uc = curl_url_set(u, CURLUPART_URL, longurl, 0);
    printf("CURLUPART_URL %d bytes URL == %d\n",
           EXCESSIVE, (int)uc);
    uc = curl_url_set(u, CURLUPART_SCHEME, longurl, CURLU_NON_SUPPORT_SCHEME);
    printf("CURLUPART_SCHEME %d bytes scheme == %d\n",
           EXCESSIVE, (int)uc);
    uc = curl_url_set(u, CURLUPART_USER, longurl, 0);
    printf("CURLUPART_USER %d bytes user == %d\n",
           EXCESSIVE, (int)uc);
    curl_url_cleanup(u);
  }

  free(longurl);

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return 0;

test_cleanup:

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res; /* return the final return code */
}