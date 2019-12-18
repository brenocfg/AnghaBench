#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* usimple_lock_t ;
typedef  int /*<<< orphan*/  simple_lock_t ;
struct TYPE_4__ {int /*<<< orphan*/  lck_spin_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  USLDBG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  usld_lock_init (TYPE_1__*,unsigned short) ; 

void
usimple_lock_init(
		  usimple_lock_t l,
		  unsigned short tag)
{
#ifndef	MACHINE_SIMPLE_LOCK
	USLDBG(usld_lock_init(l, tag));
	hw_lock_init(&l->lck_spin_data);
#else
	simple_lock_init((simple_lock_t) l, tag);
#endif
}