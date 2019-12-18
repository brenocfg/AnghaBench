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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath_hw {int dummy; } ;
struct ath9k_hw_cal_data {scalar_t__** pa_table; int /*<<< orphan*/ * small_signal_gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_CHAN_INFO_MEMORY ; 
 int /*<<< orphan*/  AR_PHY_CHAN_INFO_MEMORY_CHANINFOMEM_S2_READ ; 
 scalar_t__ AR_PHY_CHAN_INFO_TAB_0 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_READ (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ar9003_paprd_retrain_pa_in (struct ath_hw*,struct ath9k_hw_cal_data*,int) ; 
 int /*<<< orphan*/  create_pa_curve (scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

int ar9003_paprd_create_curve(struct ath_hw *ah,
			      struct ath9k_hw_cal_data *caldata, int chain)
{
	u16 *small_signal_gain = &caldata->small_signal_gain[chain];
	u32 *pa_table = caldata->pa_table[chain];
	u32 *data_L, *data_U;
	int i, status = 0;
	u32 *buf;
	u32 reg;

	memset(caldata->pa_table[chain], 0, sizeof(caldata->pa_table[chain]));

	buf = kmalloc(2 * 48 * sizeof(u32), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	data_L = &buf[0];
	data_U = &buf[48];

	REG_CLR_BIT(ah, AR_PHY_CHAN_INFO_MEMORY,
		    AR_PHY_CHAN_INFO_MEMORY_CHANINFOMEM_S2_READ);

	reg = AR_PHY_CHAN_INFO_TAB_0;
	for (i = 0; i < 48; i++)
		data_L[i] = REG_READ(ah, reg + (i << 2));

	REG_SET_BIT(ah, AR_PHY_CHAN_INFO_MEMORY,
		    AR_PHY_CHAN_INFO_MEMORY_CHANINFOMEM_S2_READ);

	for (i = 0; i < 48; i++)
		data_U[i] = REG_READ(ah, reg + (i << 2));

	if (!create_pa_curve(data_L, data_U, pa_table, small_signal_gain))
		status = -2;

	if (ar9003_paprd_retrain_pa_in(ah, caldata, chain))
		status = -EINPROGRESS;

	REG_CLR_BIT(ah, AR_PHY_PAPRD_TRAINER_STAT1,
		    AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE);

	kfree(buf);

	return status;
}