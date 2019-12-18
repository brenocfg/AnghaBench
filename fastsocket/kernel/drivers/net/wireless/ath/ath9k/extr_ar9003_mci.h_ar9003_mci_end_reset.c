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
struct ath_hw {int dummy; } ;
struct ath9k_hw_cal_data {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int ar9003_mci_end_reset(struct ath_hw *ah, struct ath9k_channel *chan,
				       struct ath9k_hw_cal_data *caldata)
{
	return 0;
}