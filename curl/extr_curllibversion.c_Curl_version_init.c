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

/* Variables and functions */
 int /*<<< orphan*/  CURLVERSION_NOW ; 
 int /*<<< orphan*/  curl_version () ; 
 int /*<<< orphan*/  curl_version_info (int /*<<< orphan*/ ) ; 

void Curl_version_init(void)
{
  curl_version();
  curl_version_info(CURLVERSION_NOW);
}