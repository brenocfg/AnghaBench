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
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int Curl_mk_dnscache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_easy_init () ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  hp ; 

__attribute__((used)) static CURLcode unit_setup(void)
{
  int rc;
  data = curl_easy_init();
  if(!data)
    return CURLE_OUT_OF_MEMORY;

  rc = Curl_mk_dnscache(&hp);
  if(rc) {
    curl_easy_cleanup(data);
    curl_global_cleanup();
    return CURLE_OUT_OF_MEMORY;
  }
  return CURLE_OK;
}