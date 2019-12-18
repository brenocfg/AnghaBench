#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct bnad_iocmd_comp {scalar_t__ comp_status; int /*<<< orphan*/  comp; struct bnad* bnad; } ;
struct TYPE_3__ {int /*<<< orphan*/  flash; } ;
struct bnad {int /*<<< orphan*/  bna_lock; TYPE_1__ bna; } ;
struct bfa_flash_attr {scalar_t__ npart; TYPE_2__* part; } ;
struct TYPE_4__ {scalar_t__ part_off; scalar_t__ part_size; scalar_t__ part_type; } ;

/* Variables and functions */
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ bfa_nw_flash_get_attr (int /*<<< orphan*/ *,struct bfa_flash_attr*,int /*<<< orphan*/ ,struct bnad_iocmd_comp*) ; 
 int /*<<< orphan*/  bnad_cb_completion ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bfa_flash_attr*) ; 
 struct bfa_flash_attr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
bnad_get_flash_partition_by_offset(struct bnad *bnad, u32 offset,
				u32 *base_offset)
{
	struct bfa_flash_attr *flash_attr;
	struct bnad_iocmd_comp fcomp;
	u32 i, flash_part = 0, ret;
	unsigned long flags = 0;

	flash_attr = kzalloc(sizeof(struct bfa_flash_attr), GFP_KERNEL);
	if (!flash_attr)
		return 0;

	fcomp.bnad = bnad;
	fcomp.comp_status = 0;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	ret = bfa_nw_flash_get_attr(&bnad->bna.flash, flash_attr,
				bnad_cb_completion, &fcomp);
	if (ret != BFA_STATUS_OK) {
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		kfree(flash_attr);
		return 0;
	}
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	wait_for_completion(&fcomp.comp);
	ret = fcomp.comp_status;

	/* Check for the flash type & base offset value */
	if (ret == BFA_STATUS_OK) {
		for (i = 0; i < flash_attr->npart; i++) {
			if (offset >= flash_attr->part[i].part_off &&
			    offset < (flash_attr->part[i].part_off +
				      flash_attr->part[i].part_size)) {
				flash_part = flash_attr->part[i].part_type;
				*base_offset = flash_attr->part[i].part_off;
				break;
			}
		}
	}
	kfree(flash_attr);
	return flash_part;
}