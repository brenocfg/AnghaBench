#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ihdlr (unsigned int) ; 
 unsigned int num_boards ; 
 TYPE_1__** sh ; 
 char* sha ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t do_interrupt_handler(int irq, void *shap) {
   unsigned int j;
   unsigned long spin_flags;
   irqreturn_t ret;

   /* Check if the interrupt must be processed by this handler */
   if ((j = (unsigned int)((char *)shap - sha)) >= num_boards) return IRQ_NONE;

   spin_lock_irqsave(sh[j]->host_lock, spin_flags);
   ret = ihdlr(j);
   spin_unlock_irqrestore(sh[j]->host_lock, spin_flags);
   return ret;
}