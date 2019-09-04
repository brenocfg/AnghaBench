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
 int /*<<< orphan*/  ccv_cache ; 
 int /*<<< orphan*/  ccv_cache_close (int /*<<< orphan*/ *) ; 
 scalar_t__ ccv_cache_opt ; 

void ccv_disable_cache(void)
{
	ccv_cache_opt = 0;
	ccv_cache_close(&ccv_cache);
}