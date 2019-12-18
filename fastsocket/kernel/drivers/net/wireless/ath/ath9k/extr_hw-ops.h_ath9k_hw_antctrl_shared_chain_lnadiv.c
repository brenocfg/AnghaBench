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
struct TYPE_2__ {int /*<<< orphan*/  (* antctrl_shared_chain_lnadiv ) (struct ath_hw*,int) ;} ;

/* Variables and functions */
 TYPE_1__* ath9k_hw_ops (struct ath_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ath_hw*,int) ; 

__attribute__((used)) static inline void ath9k_hw_antctrl_shared_chain_lnadiv(struct ath_hw *ah,
							bool enable)
{
	if (ath9k_hw_ops(ah)->antctrl_shared_chain_lnadiv)
		ath9k_hw_ops(ah)->antctrl_shared_chain_lnadiv(ah, enable);
}