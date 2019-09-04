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
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  easy ; 

__attribute__((used)) static void unit_stop(void)
{
  curl_easy_cleanup(easy);
  curl_global_cleanup();
}