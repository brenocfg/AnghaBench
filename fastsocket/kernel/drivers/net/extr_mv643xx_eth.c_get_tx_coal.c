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
typedef  int u64 ;
struct mv643xx_eth_private {TYPE_1__* shared; } ;
struct TYPE_2__ {int /*<<< orphan*/  t_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_FIFO_URGENT_THRESHOLD ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int get_tx_coal(struct mv643xx_eth_private *mp)
{
	u64 temp;

	temp = (rdlp(mp, TX_FIFO_URGENT_THRESHOLD) & 0x3fff0) >> 4;
	temp *= 64000000;
	do_div(temp, mp->shared->t_clk);

	return (unsigned int)temp;
}