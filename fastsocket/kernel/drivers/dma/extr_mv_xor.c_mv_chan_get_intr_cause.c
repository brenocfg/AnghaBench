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
 int /*<<< orphan*/  XOR_INTR_CAUSE (struct mv_xor_chan*) ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mv_chan_get_intr_cause(struct mv_xor_chan *chan)
{
	u32 intr_cause = __raw_readl(XOR_INTR_CAUSE(chan));
	intr_cause = (intr_cause >> (chan->idx * 16)) & 0xFFFF;
	return intr_cause;
}