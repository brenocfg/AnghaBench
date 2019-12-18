#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int PF_FROZEN ; 
 int PF_NOFREEZE ; 
 int /*<<< orphan*/  clear_freeze_flag (TYPE_1__*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void frozen_process(void)
{
	if (!unlikely(current->flags & PF_NOFREEZE)) {
		current->flags |= PF_FROZEN;
		wmb();
	}
	clear_freeze_flag(current);
}