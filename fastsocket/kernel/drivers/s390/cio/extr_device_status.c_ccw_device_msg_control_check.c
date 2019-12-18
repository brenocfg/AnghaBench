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
struct irb {int /*<<< orphan*/  scsw; } ;
struct ccw_device {TYPE_3__* private; } ;
struct TYPE_5__ {int sch_no; int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  devno; } ;
struct TYPE_6__ {TYPE_2__ schid; TYPE_1__ dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_HEX_EVENT (int /*<<< orphan*/ ,struct irb*,int) ; 
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int /*<<< orphan*/ ,char*) ; 
 int SCHN_STAT_CHN_CTRL_CHK ; 
 int SCHN_STAT_CHN_DATA_CHK ; 
 int SCHN_STAT_INTF_CTRL_CHK ; 
 int scsw_cstat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsw_dstat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsw_is_valid_cstat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void
ccw_device_msg_control_check(struct ccw_device *cdev, struct irb *irb)
{
	char dbf_text[15];

	if (!scsw_is_valid_cstat(&irb->scsw) ||
	    !(scsw_cstat(&irb->scsw) & (SCHN_STAT_CHN_DATA_CHK |
	      SCHN_STAT_CHN_CTRL_CHK | SCHN_STAT_INTF_CTRL_CHK)))
		return;
	CIO_MSG_EVENT(0, "Channel-Check or Interface-Control-Check "
		      "received"
		      " ... device %04x on subchannel 0.%x.%04x, dev_stat "
		      ": %02X sch_stat : %02X\n",
		      cdev->private->dev_id.devno, cdev->private->schid.ssid,
		      cdev->private->schid.sch_no,
		      scsw_dstat(&irb->scsw), scsw_cstat(&irb->scsw));
	sprintf(dbf_text, "chk%x", cdev->private->schid.sch_no);
	CIO_TRACE_EVENT(0, dbf_text);
	CIO_HEX_EVENT(0, irb, sizeof(struct irb));
}