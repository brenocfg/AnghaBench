#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kregs; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  die_if_kernel (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 

__attribute__((used)) static inline int decode_access_size(unsigned int insn)
{
	insn = (insn >> 19) & 3;

	if(!insn)
		return 4;
	else if(insn == 3)
		return 8;
	else if(insn == 2)
		return 2;
	else {
		printk("Impossible unaligned trap. insn=%08x\n", insn);
		die_if_kernel("Byte sized unaligned access?!?!", current->thread.kregs);
		return 4; /* just to keep gcc happy. */
	}
}