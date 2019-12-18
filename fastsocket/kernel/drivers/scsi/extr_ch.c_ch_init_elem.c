#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_6__ {TYPE_1__* device; } ;
typedef  TYPE_2__ scsi_changer ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {int lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int INITIALIZE_ELEMENT_STATUS ; 
 int ch_do_scsi (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vprintk (char*) ; 

__attribute__((used)) static int
ch_init_elem(scsi_changer *ch)
{
	int err;
	u_char cmd[6];

	vprintk("INITIALIZE ELEMENT STATUS, may take some time ...\n");
	memset(cmd,0,sizeof(cmd));
	cmd[0] = INITIALIZE_ELEMENT_STATUS;
	cmd[1] = ch->device->lun << 5;
	err = ch_do_scsi(ch, cmd, NULL, 0, DMA_NONE);
	vprintk("... finished\n");
	return err;
}