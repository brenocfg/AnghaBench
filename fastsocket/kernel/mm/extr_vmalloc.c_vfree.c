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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vunmap (void const*,int) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  kmemleak_free (void const*) ; 

void vfree(const void *addr)
{
	BUG_ON(in_interrupt());

	kmemleak_free(addr);

	__vunmap(addr, 1);
}