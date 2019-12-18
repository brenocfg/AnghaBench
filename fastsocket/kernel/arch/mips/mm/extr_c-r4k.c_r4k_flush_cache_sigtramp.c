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
 int /*<<< orphan*/  local_r4k_flush_cache_sigtramp ; 
 int /*<<< orphan*/  r4k_on_each_cpu (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void r4k_flush_cache_sigtramp(unsigned long addr)
{
	r4k_on_each_cpu(local_r4k_flush_cache_sigtramp, (void *) addr, 1);
}