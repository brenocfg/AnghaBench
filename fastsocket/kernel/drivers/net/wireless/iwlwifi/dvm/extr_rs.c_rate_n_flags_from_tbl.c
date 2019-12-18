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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct iwl_scale_tbl_info {int ant_type; scalar_t__ is_SGI; int /*<<< orphan*/  lq_type; scalar_t__ is_dup; scalar_t__ is_ht40; } ;
struct iwl_priv {int dummy; } ;
struct TYPE_2__ {int plcp; int plcp_siso; int plcp_mimo2; int plcp_mimo3; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,...) ; 
 int IWL_FIRST_CCK_RATE ; 
 int IWL_LAST_CCK_RATE ; 
 int IWL_LAST_OFDM_RATE ; 
 int RATE_MCS_ANT_ABC_MSK ; 
 int RATE_MCS_ANT_POS ; 
 int RATE_MCS_CCK_MSK ; 
 int RATE_MCS_DUP_MSK ; 
 int RATE_MCS_GF_MSK ; 
 int RATE_MCS_HT40_MSK ; 
 int RATE_MCS_HT_MSK ; 
 int RATE_MCS_SGI_MSK ; 
 scalar_t__ is_Ht (int /*<<< orphan*/ ) ; 
 scalar_t__ is_legacy (int /*<<< orphan*/ ) ; 
 scalar_t__ is_mimo2 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_siso (int /*<<< orphan*/ ) ; 
 TYPE_1__* iwl_rates ; 

__attribute__((used)) static u32 rate_n_flags_from_tbl(struct iwl_priv *priv,
				 struct iwl_scale_tbl_info *tbl,
				 int index, u8 use_green)
{
	u32 rate_n_flags = 0;

	if (is_legacy(tbl->lq_type)) {
		rate_n_flags = iwl_rates[index].plcp;
		if (index >= IWL_FIRST_CCK_RATE && index <= IWL_LAST_CCK_RATE)
			rate_n_flags |= RATE_MCS_CCK_MSK;

	} else if (is_Ht(tbl->lq_type)) {
		if (index > IWL_LAST_OFDM_RATE) {
			IWL_ERR(priv, "Invalid HT rate index %d\n", index);
			index = IWL_LAST_OFDM_RATE;
		}
		rate_n_flags = RATE_MCS_HT_MSK;

		if (is_siso(tbl->lq_type))
			rate_n_flags |=	iwl_rates[index].plcp_siso;
		else if (is_mimo2(tbl->lq_type))
			rate_n_flags |=	iwl_rates[index].plcp_mimo2;
		else
			rate_n_flags |=	iwl_rates[index].plcp_mimo3;
	} else {
		IWL_ERR(priv, "Invalid tbl->lq_type %d\n", tbl->lq_type);
	}

	rate_n_flags |= ((tbl->ant_type << RATE_MCS_ANT_POS) &
						     RATE_MCS_ANT_ABC_MSK);

	if (is_Ht(tbl->lq_type)) {
		if (tbl->is_ht40) {
			if (tbl->is_dup)
				rate_n_flags |= RATE_MCS_DUP_MSK;
			else
				rate_n_flags |= RATE_MCS_HT40_MSK;
		}
		if (tbl->is_SGI)
			rate_n_flags |= RATE_MCS_SGI_MSK;

		if (use_green) {
			rate_n_flags |= RATE_MCS_GF_MSK;
			if (is_siso(tbl->lq_type) && tbl->is_SGI) {
				rate_n_flags &= ~RATE_MCS_SGI_MSK;
				IWL_ERR(priv, "GF was set with SGI:SISO\n");
			}
		}
	}
	return rate_n_flags;
}