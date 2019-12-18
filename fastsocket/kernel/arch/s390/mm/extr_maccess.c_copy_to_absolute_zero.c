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
struct _lowcore {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __ctl_clear_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __ctl_load (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ctl_store (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_real (void*,void*,size_t) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int store_prefix () ; 

void copy_to_absolute_zero(void *dest, void *src, size_t count)
{
	unsigned long cr0;

	BUG_ON((unsigned long) dest + count >= sizeof(struct _lowcore));
	preempt_disable();
	__ctl_store(cr0, 0, 0);
	__ctl_clear_bit(0, 28); /* disable lowcore protection */
	memcpy_real(dest + store_prefix(), src, count);
	__ctl_load(cr0, 0, 0);
	preempt_enable();
}