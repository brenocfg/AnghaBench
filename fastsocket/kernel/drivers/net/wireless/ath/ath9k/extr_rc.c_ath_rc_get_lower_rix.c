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
typedef  scalar_t__ u8 ;
struct ath_rate_priv {size_t max_valid_rate; scalar_t__* valid_rate_index; } ;
typedef  size_t int8_t ;

/* Variables and functions */

__attribute__((used)) static inline int
ath_rc_get_lower_rix(struct ath_rate_priv *ath_rc_priv,
		     u8 cur_valid_txrate, u8 *next_idx)
{
	int8_t i;

	for (i = 1; i < ath_rc_priv->max_valid_rate ; i++) {
		if (ath_rc_priv->valid_rate_index[i] == cur_valid_txrate) {
			*next_idx = ath_rc_priv->valid_rate_index[i-1];
			return 1;
		}
	}

	return 0;
}