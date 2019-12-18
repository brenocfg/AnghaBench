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
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;int /*<<< orphan*/  (* acquire ) (struct e1000_hw*) ;} ;
struct e1000_nvm_info {scalar_t__ word_size; TYPE_3__ ops; } ;
struct e1000_dev_spec_ich8lan {TYPE_2__* shadow_ram; } ;
struct TYPE_4__ {struct e1000_dev_spec_ich8lan ich8lan; } ;
struct e1000_hw {TYPE_1__ dev_spec; struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {int modified; scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_NVM ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_write_nvm_ich8lan(struct e1000_hw *hw, u16 offset, u16 words,
				   u16 *data)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	struct e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u16 i;

	if ((offset >= nvm->word_size) || (words > nvm->word_size - offset) ||
	    (words == 0)) {
		e_dbg("nvm parameter(s) out of bounds\n");
		return -E1000_ERR_NVM;
	}

	nvm->ops.acquire(hw);

	for (i = 0; i < words; i++) {
		dev_spec->shadow_ram[offset + i].modified = true;
		dev_spec->shadow_ram[offset + i].value = data[i];
	}

	nvm->ops.release(hw);

	return 0;
}