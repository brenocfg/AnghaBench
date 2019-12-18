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
typedef  int /*<<< orphan*/  u32 ;
struct mv_xor_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XOR_INIT_VALUE_HIGH (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_INIT_VALUE_LOW (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_chan_set_value(struct mv_xor_chan *chan, u32 value)
{
	__raw_writel(value, XOR_INIT_VALUE_LOW(chan));
	__raw_writel(value, XOR_INIT_VALUE_HIGH(chan));
}