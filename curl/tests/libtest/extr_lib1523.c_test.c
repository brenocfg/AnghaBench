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
 int CURLE_OPERATION_TIMEDOUT ; 
 int /*<<< orphan*/  CURLOPT_ERRORBUFFER ; 
 int /*<<< orphan*/  CURLOPT_NOPROGRESS ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_XFERINFOFUNCTION ; 
 int CURL_ERROR_SIZE ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 long dload_progress_cb ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int run (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int time (int /*<<< orphan*/ *) ; 
 long write_cb ; 

int test(char *URL)
{
  CURLcode ret;
  CURL *hnd = curl_easy_init();
  char buffer[CURL_ERROR_SIZE];
  curl_easy_setopt(hnd, CURLOPT_URL, URL);
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_cb);
  curl_easy_setopt(hnd, CURLOPT_ERRORBUFFER, buffer);
  curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 0L);
  curl_easy_setopt(hnd, CURLOPT_XFERINFOFUNCTION, dload_progress_cb);

  printf("Start: %d\n", time(NULL));
  ret = run(hnd, 1, 2);
  if(ret)
    fprintf(stderr, "error %d: %s\n", ret, buffer);

  ret = run(hnd, 12000, 1);
  if(ret != CURLE_OPERATION_TIMEDOUT)
    fprintf(stderr, "error %d: %s\n", ret, buffer);
  else
    ret = 0;

  printf("End: %d\n", time(NULL));
  curl_easy_cleanup(hnd);

  return (int)ret;
}