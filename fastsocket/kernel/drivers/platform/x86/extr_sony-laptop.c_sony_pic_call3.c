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
typedef  int u8 ;
struct TYPE_6__ {TYPE_2__* cur_ioport; } ;
struct TYPE_4__ {scalar_t__ minimum; } ;
struct TYPE_5__ {TYPE_1__ io1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITERATIONS_LONG ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int,int) ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 TYPE_3__ spic_dev ; 
 int /*<<< orphan*/  wait_on_command (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 sony_pic_call3(u8 dev, u8 fn, u8 v)
{
	u8 v1;

	wait_on_command(inb_p(spic_dev.cur_ioport->io1.minimum + 4) & 2, ITERATIONS_LONG);
	outb(dev, spic_dev.cur_ioport->io1.minimum + 4);
	wait_on_command(inb_p(spic_dev.cur_ioport->io1.minimum + 4) & 2, ITERATIONS_LONG);
	outb(fn, spic_dev.cur_ioport->io1.minimum);
	wait_on_command(inb_p(spic_dev.cur_ioport->io1.minimum + 4) & 2, ITERATIONS_LONG);
	outb(v, spic_dev.cur_ioport->io1.minimum);
	v1 = inb_p(spic_dev.cur_ioport->io1.minimum);
	dprintk("sony_pic_call3(0x%.2x - 0x%.2x - 0x%.2x): 0x%.4x\n",
			dev, fn, v, v1);
	return v1;
}