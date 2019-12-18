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
struct curl_slist {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  HOST ; 
 int NUM_HANDLES ; 
 int /*<<< orphan*/  PROXYUSERPWD ; 
 int TEST_ERR_MAJOR_BAD ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct curl_slist* curl_slist_append (struct curl_slist*,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 int /*<<< orphan*/ ** eh ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int loop (int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct curl_slist*) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_test_timing () ; 
 int /*<<< orphan*/  stderr ; 
 int test_argc ; 

int test(char *URL)
{
  CURLM *cm = NULL;
  struct curl_slist *headers = NULL;
  char buffer[246]; /* naively fixed-size */
  int res = 0;
  int i;

  for(i = 0; i < NUM_HANDLES; i++)
    eh[i] = NULL;

  start_test_timing();

  if(test_argc < 4)
    return 99;

  msnprintf(buffer, sizeof(buffer), "Host: %s", HOST);

  /* now add a custom Host: header */
  headers = curl_slist_append(headers, buffer);
  if(!headers) {
    fprintf(stderr, "curl_slist_append() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  res_global_init(CURL_GLOBAL_ALL);
  if(res) {
    curl_slist_free_all(headers);
    return res;
  }

  res_multi_init(cm);
  if(res) {
    curl_global_cleanup();
    curl_slist_free_all(headers);
    return res;
  }

  res = loop(0, cm, URL, PROXYUSERPWD, headers);
  if(res)
    goto test_cleanup;

  fprintf(stderr, "lib540: now we do the request again\n");

  res = loop(1, cm, URL, PROXYUSERPWD, headers);

test_cleanup:

  /* proper cleanup sequence - type PB */

  for(i = 0; i < NUM_HANDLES; i++) {
    curl_multi_remove_handle(cm, eh[i]);
    curl_easy_cleanup(eh[i]);
  }

  curl_multi_cleanup(cm);
  curl_global_cleanup();

  curl_slist_free_all(headers);

  return res;
}