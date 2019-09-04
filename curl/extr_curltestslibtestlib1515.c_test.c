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
typedef  int /*<<< orphan*/  dns_entry ;
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 scalar_t__ DNS_TIMEOUT ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int do_one_request (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 
 char* libtest_arg2 ; 
 char* libtest_arg3 ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,char*,char*,...) ; 
 int /*<<< orphan*/  multi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (scalar_t__) ; 
 int /*<<< orphan*/  start_test_timing () ; 

int test(char *URL)
{
  CURLM *multi = NULL;
  int res = 0;
  char *address = libtest_arg2;
  char *port = libtest_arg3;
  char *path = URL;
  char dns_entry[256];
  int i;
  int count = 2;

  msnprintf(dns_entry, sizeof(dns_entry), "testserver.example.com:%s:%s",
            port, address);

  start_test_timing();

  global_init(CURL_GLOBAL_ALL);
  multi_init(multi);

  for(i = 1; i <= count; i++) {
    char target_url[256];
    msnprintf(target_url, sizeof(target_url),
              "http://testserver.example.com:%s/%s%04d", port, path, i);

    /* second request must succeed like the first one */
    res = do_one_request(multi, target_url, dns_entry);
    if(res)
      goto test_cleanup;

    if(i < count)
      sleep(DNS_TIMEOUT + 1);
  }

test_cleanup:

  curl_multi_cleanup(multi);
  curl_global_cleanup();

  return (int) res;
}