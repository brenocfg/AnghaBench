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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct hpsa_scsi_dev_t {int dummy; } ;
struct ctlr_info {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  hpsa_set_bus_target_lun (struct hpsa_scsi_dev_t*,int,int,int) ; 
 scalar_t__ is_ext_target (struct ctlr_info*,struct hpsa_scsi_dev_t*) ; 
 scalar_t__ is_hba_lunid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_logical_dev_addr_mode (int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void figure_bus_target_lun(struct ctlr_info *h,
	u8 *lunaddrbytes, struct hpsa_scsi_dev_t *device)
{
	u32 lunid = le32_to_cpu(*((__le32 *) lunaddrbytes));

	if (!is_logical_dev_addr_mode(lunaddrbytes)) {
		/* physical device, target and lun filled in later */
		if (is_hba_lunid(lunaddrbytes))
			hpsa_set_bus_target_lun(device, 3, 0, lunid & 0x3fff);
		else
			/* defer target, lun assignment for physical devices */
			hpsa_set_bus_target_lun(device, 2, -1, -1);
		return;
	}
	/* It's a logical device */
	if (is_ext_target(h, device)) {
		/* external target way, put logicals on bus 1
		 * and match target/lun numbers box
		 * reports, other smart array, bus 0, target 0, match lunid
		 */
		hpsa_set_bus_target_lun(device,
			1, (lunid >> 16) & 0x3fff, lunid & 0x00ff);
		return;
	}
	hpsa_set_bus_target_lun(device, 0, 0, lunid & 0x3fff);
}