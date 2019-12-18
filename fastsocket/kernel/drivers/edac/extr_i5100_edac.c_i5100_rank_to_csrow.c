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
struct mem_ctl_info {struct i5100_priv* pvt_info; } ;
struct i5100_priv {int ranksperctlr; } ;

/* Variables and functions */

__attribute__((used)) static unsigned i5100_rank_to_csrow(const struct mem_ctl_info *mci,
				    int ctlr, int rank)
{
	const struct i5100_priv *priv = mci->pvt_info;

	return ctlr * priv->ranksperctlr + rank;
}