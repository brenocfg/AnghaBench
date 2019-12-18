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
typedef  int u8 ;
struct ath_rate_table {int dummy; } ;
struct ath_rate_priv {int max_valid_rate; int* valid_rate_index; } ;

/* Variables and functions */

__attribute__((used)) static inline
int ath_rc_get_nextvalid_txrate(const struct ath_rate_table *rate_table,
				struct ath_rate_priv *ath_rc_priv,
				u8 cur_valid_txrate,
				u8 *next_idx)
{
	u8 i;

	for (i = 0; i < ath_rc_priv->max_valid_rate - 1; i++) {
		if (ath_rc_priv->valid_rate_index[i] == cur_valid_txrate) {
			*next_idx = ath_rc_priv->valid_rate_index[i+1];
			return 1;
		}
	}

	/* No more valid rates */
	*next_idx = 0;

	return 0;
}