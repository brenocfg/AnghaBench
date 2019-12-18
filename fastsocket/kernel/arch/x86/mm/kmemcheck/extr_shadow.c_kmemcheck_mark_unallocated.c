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
 int /*<<< orphan*/  KMEMCHECK_SHADOW_UNALLOCATED ; 
 int /*<<< orphan*/  mark_shadow (void*,unsigned int,int /*<<< orphan*/ ) ; 

void kmemcheck_mark_unallocated(void *address, unsigned int n)
{
	mark_shadow(address, n, KMEMCHECK_SHADOW_UNALLOCATED);
}