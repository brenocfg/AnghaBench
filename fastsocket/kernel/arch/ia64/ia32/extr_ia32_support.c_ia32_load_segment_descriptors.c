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
struct task_struct {int dummy; } ;
struct pt_regs {int r16; int r17; void* ar_ssd; void* ar_csd; void* r29; void* r28; void* r27; void* r24; } ;

/* Variables and functions */
 void* load_desc (int) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

void
ia32_load_segment_descriptors (struct task_struct *task)
{
	struct pt_regs *regs = task_pt_regs(task);

	/* Setup the segment descriptors */
	regs->r24 = load_desc(regs->r16 >> 16);		/* ESD */
	regs->r27 = load_desc(regs->r16 >>  0);		/* DSD */
	regs->r28 = load_desc(regs->r16 >> 32);		/* FSD */
	regs->r29 = load_desc(regs->r16 >> 48);		/* GSD */
	regs->ar_csd = load_desc(regs->r17 >>  0);	/* CSD */
	regs->ar_ssd = load_desc(regs->r17 >> 16);	/* SSD */
}