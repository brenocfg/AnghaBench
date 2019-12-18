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
typedef  int u8 ;
struct ath_rate_table {TYPE_1__* info; } ;
struct ath_rate_priv {int max_valid_rate; int* valid_rate_index; struct ath_rate_table* rate_table; } ;
struct TYPE_2__ {scalar_t__ ratekbps; } ;

/* Variables and functions */

__attribute__((used)) static void ath_rc_sort_validrates(struct ath_rate_priv *ath_rc_priv)
{
	const struct ath_rate_table *rate_table = ath_rc_priv->rate_table;
	u8 i, j, idx, idx_next;

	for (i = ath_rc_priv->max_valid_rate - 1; i > 0; i--) {
		for (j = 0; j <= i-1; j++) {
			idx = ath_rc_priv->valid_rate_index[j];
			idx_next = ath_rc_priv->valid_rate_index[j+1];

			if (rate_table->info[idx].ratekbps >
				rate_table->info[idx_next].ratekbps) {
				ath_rc_priv->valid_rate_index[j] = idx_next;
				ath_rc_priv->valid_rate_index[j+1] = idx;
			}
		}
	}
}