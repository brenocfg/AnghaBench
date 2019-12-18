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
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_LOW_SPEED_LIMIT ; 
 int /*<<< orphan*/  CURLOPT_LOW_SPEED_TIME ; 
 int /*<<< orphan*/  curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static CURLcode run(CURL *hnd, long limit, long time)
{
  curl_easy_setopt(hnd, CURLOPT_LOW_SPEED_LIMIT, limit);
  curl_easy_setopt(hnd, CURLOPT_LOW_SPEED_TIME, time);
  return curl_easy_perform(hnd);
}