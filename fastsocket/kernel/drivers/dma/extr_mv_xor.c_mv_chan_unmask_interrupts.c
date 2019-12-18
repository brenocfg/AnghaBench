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
typedef  int u32 ;
struct mv_xor_chan {int idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  XOR_INTR_MASK (struct mv_xor_chan*) ; 
 int XOR_INTR_MASK_VALUE ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_chan_unmask_interrupts(struct mv_xor_chan *chan)
{
	u32 val = __raw_readl(XOR_INTR_MASK(chan));
	val |= XOR_INTR_MASK_VALUE << (chan->idx * 16);
	__raw_writel(val, XOR_INTR_MASK(chan));
}