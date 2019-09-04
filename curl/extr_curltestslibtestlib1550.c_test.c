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
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 int CURLE_OK ; 
 int /*<<< orphan*/  CURLMOPT_PIPELINING_SERVER_BL ; 
 int /*<<< orphan*/  CURLMOPT_PIPELINING_SITE_BL ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_multi_init () ; 
 int /*<<< orphan*/  curl_multi_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const* const*) ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 

int test(char *URL)
{
  CURLM *handle;
  int res = CURLE_OK;
  static const char * const bl_servers[] =
     {"Microsoft-IIS/6.0", "nginx/0.8.54", NULL};
  static const char * const bl_sites[] =
     {"curl.haxx.se:443", "example.com:80", NULL};

  global_init(CURL_GLOBAL_ALL);
  handle = curl_multi_init();
  (void)URL; /* unused */

  curl_multi_setopt(handle, CURLMOPT_PIPELINING_SERVER_BL, bl_servers);
  curl_multi_setopt(handle, CURLMOPT_PIPELINING_SITE_BL, bl_sites);
  curl_multi_cleanup(handle);
  curl_global_cleanup();
  return 0;
}