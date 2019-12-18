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
typedef  int /*<<< orphan*/  target_url ;
typedef  char curl_slist ;
typedef  int /*<<< orphan*/  dnsentry ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_MAXCONNECTS ; 
 int /*<<< orphan*/  CURLOPT_RESOLVE ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int NUM_URLS ; 
 int /*<<< orphan*/  abort_on_test_timeout () ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 char* curl_slist_append (char*,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (char*) ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 char* libtest_arg2 ; 
 char* libtest_arg3 ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,int,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  start_test_timing () ; 
 int /*<<< orphan*/  stderr ; 

int test(char *URL)
{
  int res = 0;
  CURL *curl = NULL;
  int i;
  char target_url[256];
  char dnsentry[256];
  struct curl_slist *slist = NULL, *slist2;
  char *port = libtest_arg3;
  char *address = libtest_arg2;

  (void)URL;

  /* Create fake DNS entries for serverX.example.com for all handles */
  for(i = 0; i < NUM_URLS; i++) {
    msnprintf(dnsentry, sizeof(dnsentry), "server%d.example.com:%s:%s", i + 1,
              port, address);
    printf("%s\n", dnsentry);
    slist2 = curl_slist_append(slist, dnsentry);
    if(!slist2) {
      fprintf(stderr, "curl_slist_append() failed\n");
      goto test_cleanup;
    }
    slist = slist2;
  }

  start_test_timing();

  global_init(CURL_GLOBAL_ALL);

  /* get an easy handle */
  easy_init(curl);

  /* go verbose */
  easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  /* include headers */
  easy_setopt(curl, CURLOPT_HEADER, 1L);

  easy_setopt(curl, CURLOPT_RESOLVE, slist);

  easy_setopt(curl, CURLOPT_MAXCONNECTS, 3L);

  /* get NUM_HANDLES easy handles */
  for(i = 0; i < NUM_URLS; i++) {
    /* specify target */
    msnprintf(target_url, sizeof(target_url),
              "http://server%d.example.com:%s/path/1510%04i",
              i + 1, port, i + 1);
    target_url[sizeof(target_url) - 1] = '\0';
    easy_setopt(curl, CURLOPT_URL, target_url);

    res = curl_easy_perform(curl);

    abort_on_test_timeout();
  }

test_cleanup:

  /* proper cleanup sequence - type PB */

  curl_easy_cleanup(curl);

  curl_slist_free_all(slist);

  curl_global_cleanup();

  return res;
}