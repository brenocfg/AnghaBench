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
struct ath_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_cal_settings ) (struct ath_hw*) ;} ;

/* Variables and functions */
 TYPE_1__* ath9k_hw_private_ops (struct ath_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ath_hw*) ; 

__attribute__((used)) static void ath9k_hw_init_cal_settings(struct ath_hw *ah)
{
	ath9k_hw_private_ops(ah)->init_cal_settings(ah);
}