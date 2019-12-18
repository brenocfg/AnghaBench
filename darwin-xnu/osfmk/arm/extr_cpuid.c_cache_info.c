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
typedef  int /*<<< orphan*/  cache_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpuid_cache_info ; 

cache_info_t   *
cache_info(void)
{
	return &cpuid_cache_info;
}