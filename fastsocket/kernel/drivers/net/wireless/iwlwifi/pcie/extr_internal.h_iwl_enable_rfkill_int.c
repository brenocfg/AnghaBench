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
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_INT_BIT_RF_KILL ; 
 int /*<<< orphan*/  CSR_INT_MASK ; 
 int /*<<< orphan*/  IWL_DEBUG_ISR (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iwl_enable_rfkill_int(struct iwl_trans *trans)
{
	IWL_DEBUG_ISR(trans, "Enabling rfkill interrupt\n");
	iwl_write32(trans, CSR_INT_MASK, CSR_INT_BIT_RF_KILL);
}