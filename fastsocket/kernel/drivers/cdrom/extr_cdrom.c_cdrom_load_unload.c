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
struct packet_command {int* cmd; int timeout; } ;
struct cdrom_device_info {int sanyo_slot; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CD_CHANGER ; 
 int /*<<< orphan*/  CGC_DATA_NONE ; 
 int GPCMD_LOAD_UNLOAD ; 
 int GPCMD_TEST_UNIT_READY ; 
 int HZ ; 
 int /*<<< orphan*/  cdinfo (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static int cdrom_load_unload(struct cdrom_device_info *cdi, int slot) 
{
	struct packet_command cgc;

	cdinfo(CD_CHANGER, "entering cdrom_load_unload()\n"); 
	if (cdi->sanyo_slot && slot < 0)
		return 0;

	init_cdrom_command(&cgc, NULL, 0, CGC_DATA_NONE);
	cgc.cmd[0] = GPCMD_LOAD_UNLOAD;
	cgc.cmd[4] = 2 + (slot >= 0);
	cgc.cmd[8] = slot;
	cgc.timeout = 60 * HZ;

	/* The Sanyo 3 CD changer uses byte 7 of the 
	GPCMD_TEST_UNIT_READY to command to switch CDs instead of
	using the GPCMD_LOAD_UNLOAD opcode. */
	if (cdi->sanyo_slot && -1 < slot) {
		cgc.cmd[0] = GPCMD_TEST_UNIT_READY;
		cgc.cmd[7] = slot;
		cgc.cmd[4] = cgc.cmd[8] = 0;
		cdi->sanyo_slot = slot ? slot : 3;
	}

	return cdi->ops->generic_packet(cdi, &cgc);
}