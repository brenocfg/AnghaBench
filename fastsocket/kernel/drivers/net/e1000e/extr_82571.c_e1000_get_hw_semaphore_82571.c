#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int smb_counter; } ;
struct TYPE_6__ {TYPE_2__ e82571; } ;
struct TYPE_4__ {int word_size; } ;
struct e1000_hw {TYPE_3__ dev_spec; TYPE_1__ nvm; } ;
typedef  int s32 ;

/* Variables and functions */
 int E1000_ERR_NVM ; 
 int E1000_SWSM_SMBI ; 
 int E1000_SWSM_SWESMBI ; 
 int /*<<< orphan*/  SWSM ; 
 int /*<<< orphan*/  e1000_put_hw_semaphore_82571 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 e1000_get_hw_semaphore_82571(struct e1000_hw *hw)
{
	u32 swsm;
	s32 sw_timeout = hw->nvm.word_size + 1;
	s32 fw_timeout = hw->nvm.word_size + 1;
	s32 i = 0;

	/* If we have timedout 3 times on trying to acquire
	 * the inter-port SMBI semaphore, there is old code
	 * operating on the other port, and it is not
	 * releasing SMBI. Modify the number of times that
	 * we try for the semaphore to interwork with this
	 * older code.
	 */
	if (hw->dev_spec.e82571.smb_counter > 2)
		sw_timeout = 1;

	/* Get the SW semaphore */
	while (i < sw_timeout) {
		swsm = er32(SWSM);
		if (!(swsm & E1000_SWSM_SMBI))
			break;

		usleep_range(50, 100);
		i++;
	}

	if (i == sw_timeout) {
		e_dbg("Driver can't access device - SMBI bit is set.\n");
		hw->dev_spec.e82571.smb_counter++;
	}
	/* Get the FW semaphore. */
	for (i = 0; i < fw_timeout; i++) {
		swsm = er32(SWSM);
		ew32(SWSM, swsm | E1000_SWSM_SWESMBI);

		/* Semaphore acquired if bit latched */
		if (er32(SWSM) & E1000_SWSM_SWESMBI)
			break;

		usleep_range(50, 100);
	}

	if (i == fw_timeout) {
		/* Release semaphores */
		e1000_put_hw_semaphore_82571(hw);
		e_dbg("Driver can't access the NVM\n");
		return -E1000_ERR_NVM;
	}

	return 0;
}