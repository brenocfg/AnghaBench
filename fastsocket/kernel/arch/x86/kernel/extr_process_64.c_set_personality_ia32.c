#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* mm; int /*<<< orphan*/  personality; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMF_COMPAT ; 
 int /*<<< orphan*/  TIF_IA32 ; 
 int /*<<< orphan*/  TS_COMPAT ; 
 TYPE_3__* current ; 
 TYPE_2__* current_thread_info () ; 
 int /*<<< orphan*/  force_personality32 ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 

void set_personality_ia32(void)
{
	/* inherit personality from parent */

	/* Make sure to be in 32bit mode */
	set_thread_flag(TIF_IA32);
	current->personality |= force_personality32;

	/* Mark the associated mm as containing 32-bit tasks. */
	set_bit(MMF_COMPAT, &current->mm->flags);

	/* Prepare the first "return" to user space */
	current_thread_info()->status |= TS_COMPAT;
}