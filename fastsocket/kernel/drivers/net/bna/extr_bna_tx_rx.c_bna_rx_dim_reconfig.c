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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ ** dim_vector; } ;
struct bna {TYPE_1__ rx_mod; } ;

/* Variables and functions */
 int BNA_BIAS_T_MAX ; 
 int BNA_LOAD_T_MAX ; 

void
bna_rx_dim_reconfig(struct bna *bna, const u32 vector[][BNA_BIAS_T_MAX])
{
	int i, j;

	for (i = 0; i < BNA_LOAD_T_MAX; i++)
		for (j = 0; j < BNA_BIAS_T_MAX; j++)
			bna->rx_mod.dim_vector[i][j] = vector[i][j];
}