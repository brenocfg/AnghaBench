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
struct flash_section_info_g2 {TYPE_2__* fsec_entry; } ;
struct flash_section_info {TYPE_1__* fsec_entry; } ;
struct be_adapter {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ BE2_chip (struct be_adapter*) ; 
 int MAX_FLASH_COMP ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_comp_in_ufi(struct be_adapter *adapter,
			   struct flash_section_info *fsec, int type)
{
	int i = 0, img_type = 0;
	struct flash_section_info_g2 *fsec_g2 = NULL;

	if (BE2_chip(adapter))
		fsec_g2 = (struct flash_section_info_g2 *)fsec;

	for (i = 0; i < MAX_FLASH_COMP; i++) {
		if (fsec_g2)
			img_type = le32_to_cpu(fsec_g2->fsec_entry[i].type);
		else
			img_type = le32_to_cpu(fsec->fsec_entry[i].type);

		if (img_type == type)
			return true;
	}
	return false;

}