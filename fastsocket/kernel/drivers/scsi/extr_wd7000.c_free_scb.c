#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ Scb ;

/* Variables and functions */
 int /*<<< orphan*/  freescbs ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* scbfree ; 
 int /*<<< orphan*/  scbpool_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void free_scb(Scb * scb)
{
	unsigned long flags;

	spin_lock_irqsave(&scbpool_lock, flags);

	memset(scb, 0, sizeof(Scb));
	scb->next = scbfree;
	scbfree = scb;
	freescbs++;

	spin_unlock_irqrestore(&scbpool_lock, flags);
}