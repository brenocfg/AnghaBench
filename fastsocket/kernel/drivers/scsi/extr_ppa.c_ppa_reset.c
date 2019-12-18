#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ phase; } ;
struct scsi_cmnd {TYPE_2__ SCp; TYPE_1__* device; } ;
struct TYPE_9__ {int /*<<< orphan*/  base; int /*<<< orphan*/ * cur_cmd; } ;
typedef  TYPE_3__ ppa_struct ;
struct TYPE_7__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_NORMAL ; 
 int SUCCESS ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  ppa_connect (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ppa_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppa_disconnect (TYPE_3__*) ; 
 int /*<<< orphan*/  ppa_reset_pulse (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppa_reset(struct scsi_cmnd *cmd)
{
	ppa_struct *dev = ppa_dev(cmd->device->host);

	if (cmd->SCp.phase)
		ppa_disconnect(dev);
	dev->cur_cmd = NULL;	/* Forget the problem */

	ppa_connect(dev, CONNECT_NORMAL);
	ppa_reset_pulse(dev->base);
	mdelay(1);		/* device settle delay */
	ppa_disconnect(dev);
	mdelay(1);		/* device settle delay */
	return SUCCESS;
}