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
 int /*<<< orphan*/  CCV_DEFAULT_CACHE_SIZE ; 
 int /*<<< orphan*/  ccv_enable_cache (int /*<<< orphan*/ ) ; 

void ccv_enable_default_cache(void)
{
	ccv_enable_cache(CCV_DEFAULT_CACHE_SIZE);
}