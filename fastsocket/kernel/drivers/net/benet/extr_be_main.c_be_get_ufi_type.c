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
struct flash_file_hdr_g3 {char* build; int asic_type_rev; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BE2_chip (struct be_adapter*) ; 
 scalar_t__ BE3_chip (struct be_adapter*) ; 
 int UFI_TYPE2 ; 
 int UFI_TYPE3 ; 
 int UFI_TYPE3R ; 
 int UFI_TYPE4 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ skyhawk_chip (struct be_adapter*) ; 

__attribute__((used)) static int be_get_ufi_type(struct be_adapter *adapter,
			   struct flash_file_hdr_g3 *fhdr)
{
	if (fhdr == NULL)
		goto be_get_ufi_exit;

	if (skyhawk_chip(adapter) && fhdr->build[0] == '4')
		return UFI_TYPE4;
	else if (BE3_chip(adapter) && fhdr->build[0] == '3') {
		if (fhdr->asic_type_rev == 0x10)
			return UFI_TYPE3R;
		else
			return UFI_TYPE3;
	} else if (BE2_chip(adapter) && fhdr->build[0] == '2')
		return UFI_TYPE2;

be_get_ufi_exit:
	dev_err(&adapter->pdev->dev,
		"UFI and Interface are not compatible for flashing\n");
	return -1;
}