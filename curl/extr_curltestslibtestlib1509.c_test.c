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
 int /*<<< orphan*/  CURLINFO_HEADER_SIZE ; 
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_HEADERFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_HTTPPROXYTUNNEL ; 
 int /*<<< orphan*/  CURLOPT_PROXY ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int TEST_ERR_MAJOR_BAD ; 
 long* WriteHeader ; 
 long* WriteOutput ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long*) ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 char* curl_easy_strerror (scalar_t__) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int,char*) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 long libtest_arg2 ; 
 int /*<<< orphan*/  printf (char*,long) ; 
 long realHeaderSize ; 
 int /*<<< orphan*/  stderr ; 

int test(char *URL)
{
  long headerSize;
  CURLcode code;
  CURL *curl = NULL;
  int res = 0;

  global_init(CURL_GLOBAL_ALL);

  easy_init(curl);

  easy_setopt(curl, CURLOPT_PROXY, libtest_arg2); /* set in first.c */

  easy_setopt(curl, CURLOPT_WRITEFUNCTION, *WriteOutput);
  easy_setopt(curl, CURLOPT_HEADERFUNCTION, *WriteHeader);

  easy_setopt(curl, CURLOPT_HEADER, 1L);
  easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  easy_setopt(curl, CURLOPT_URL, URL);
  easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1L);

  code = curl_easy_perform(curl);
  if(CURLE_OK != code) {
    fprintf(stderr, "%s:%d curl_easy_perform() failed, "
            "with code %d (%s)\n",
            __FILE__, __LINE__, (int)code, curl_easy_strerror(code));
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }

  code = curl_easy_getinfo(curl, CURLINFO_HEADER_SIZE, &headerSize);
  if(CURLE_OK != code) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed, "
            "with code %d (%s)\n",
            __FILE__, __LINE__, (int)code, curl_easy_strerror(code));
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }

  printf("header length is ........: %ld\n", headerSize);
  printf("header length should be..: %lu\n", realHeaderSize);

test_cleanup:

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}