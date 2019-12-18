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
typedef  int /*<<< orphan*/  u32 ;
struct mv_xor_chan {TYPE_2__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  XOR_ACTIVATION (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_CONFIG (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_ERROR_ADDR (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_ERROR_CAUSE (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_INTR_CAUSE (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_INTR_MASK (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_dump_xor_regs(struct mv_xor_chan *chan)
{
	u32 val;

	val = __raw_readl(XOR_CONFIG(chan));
	dev_printk(KERN_ERR, chan->device->common.dev,
		   "config       0x%08x.\n", val);

	val = __raw_readl(XOR_ACTIVATION(chan));
	dev_printk(KERN_ERR, chan->device->common.dev,
		   "activation   0x%08x.\n", val);

	val = __raw_readl(XOR_INTR_CAUSE(chan));
	dev_printk(KERN_ERR, chan->device->common.dev,
		   "intr cause   0x%08x.\n", val);

	val = __raw_readl(XOR_INTR_MASK(chan));
	dev_printk(KERN_ERR, chan->device->common.dev,
		   "intr mask    0x%08x.\n", val);

	val = __raw_readl(XOR_ERROR_CAUSE(chan));
	dev_printk(KERN_ERR, chan->device->common.dev,
		   "error cause  0x%08x.\n", val);

	val = __raw_readl(XOR_ERROR_ADDR(chan));
	dev_printk(KERN_ERR, chan->device->common.dev,
		   "error addr   0x%08x.\n", val);
}