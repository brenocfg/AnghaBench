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
typedef  unsigned int u32 ;
struct sram_channel {unsigned int name; int fifo_size; scalar_t__ cnt2_reg; scalar_t__ cnt1_reg; scalar_t__ ptr2_reg; scalar_t__ ptr1_reg; scalar_t__ ctrl_start; int /*<<< orphan*/  fifo_start; scalar_t__ cmds_start; } ;
struct cx88_core {unsigned int name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 unsigned int cx88_risc_decode (unsigned int) ; 
 unsigned int cx_read (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,...) ; 

void cx88_sram_channel_dump(struct cx88_core *core,
			    struct sram_channel *ch)
{
	static char *name[] = {
		"initial risc",
		"cdt base",
		"cdt size",
		"iq base",
		"iq size",
		"risc pc",
		"iq wr ptr",
		"iq rd ptr",
		"cdt current",
		"pci target",
		"line / byte",
	};
	u32 risc;
	unsigned int i,j,n;

	printk("%s: %s - dma channel status dump\n",
	       core->name,ch->name);
	for (i = 0; i < ARRAY_SIZE(name); i++)
		printk("%s:   cmds: %-12s: 0x%08x\n",
		       core->name,name[i],
		       cx_read(ch->cmds_start + 4*i));
	for (n = 1, i = 0; i < 4; i++) {
		risc = cx_read(ch->cmds_start + 4 * (i+11));
		printk("%s:   risc%d: ", core->name, i);
		if (--n)
			printk("0x%08x [ arg #%d ]\n", risc, n);
		else
			n = cx88_risc_decode(risc);
	}
	for (i = 0; i < 16; i += n) {
		risc = cx_read(ch->ctrl_start + 4 * i);
		printk("%s:   iq %x: ", core->name, i);
		n = cx88_risc_decode(risc);
		for (j = 1; j < n; j++) {
			risc = cx_read(ch->ctrl_start + 4 * (i+j));
			printk("%s:   iq %x: 0x%08x [ arg #%d ]\n",
			       core->name, i+j, risc, j);
		}
	}

	printk("%s: fifo: 0x%08x -> 0x%x\n",
	       core->name, ch->fifo_start, ch->fifo_start+ch->fifo_size);
	printk("%s: ctrl: 0x%08x -> 0x%x\n",
	       core->name, ch->ctrl_start, ch->ctrl_start+6*16);
	printk("%s:   ptr1_reg: 0x%08x\n",
	       core->name,cx_read(ch->ptr1_reg));
	printk("%s:   ptr2_reg: 0x%08x\n",
	       core->name,cx_read(ch->ptr2_reg));
	printk("%s:   cnt1_reg: 0x%08x\n",
	       core->name,cx_read(ch->cnt1_reg));
	printk("%s:   cnt2_reg: 0x%08x\n",
	       core->name,cx_read(ch->cnt2_reg));
}