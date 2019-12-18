#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int myid; struct TYPE_4__* next; } ;
typedef  TYPE_1__ capidrv_contr ;
struct TYPE_5__ {TYPE_1__* contr_list; } ;

/* Variables and functions */
 TYPE_2__ global ; 
 int /*<<< orphan*/  global_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline capidrv_contr *findcontrbydriverid(int driverid)
{
    	unsigned long flags;
	capidrv_contr *p;

	spin_lock_irqsave(&global_lock, flags);
	for (p = global.contr_list; p; p = p->next)
		if (p->myid == driverid)
			break;
	spin_unlock_irqrestore(&global_lock, flags);
	return p;
}