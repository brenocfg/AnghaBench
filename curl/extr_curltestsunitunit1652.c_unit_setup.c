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
 int /*<<< orphan*/  CURLOPT_DEBUGFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  data ; 
 long debugf_cb ; 
 int /*<<< orphan*/  global_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode
unit_setup(void)
{
  int res = 0;

  global_init(CURL_GLOBAL_ALL);
  data = curl_easy_init();
  if(!data)
    return CURLE_OUT_OF_MEMORY;
  curl_easy_setopt(data, CURLOPT_DEBUGFUNCTION, debugf_cb);
  curl_easy_setopt(data, CURLOPT_VERBOSE, 1L);
  return CURLE_OK;
}