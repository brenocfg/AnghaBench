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
struct TYPE_2__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct subchannel {int lpm; int /*<<< orphan*/  schib; int /*<<< orphan*/  dev; TYPE_1__ schid; } ;
struct schib {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_HEX_EVENT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int /*<<< orphan*/ ,char*) ; 
 int EACCES ; 
 int ENODEV ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static int
cio_start_handle_notoper(struct subchannel *sch, __u8 lpm)
{
	char dbf_text[15];

	if (lpm != 0)
		sch->lpm &= ~lpm;
	else
		sch->lpm = 0;

	CIO_MSG_EVENT(2, "cio_start: 'not oper' status for "
		      "subchannel 0.%x.%04x!\n", sch->schid.ssid,
		      sch->schid.sch_no);

	if (cio_update_schib(sch))
		return -ENODEV;

	sprintf(dbf_text, "no%s", dev_name(&sch->dev));
	CIO_TRACE_EVENT(0, dbf_text);
	CIO_HEX_EVENT(0, &sch->schib, sizeof (struct schib));

	return (sch->lpm ? -EACCES : -ENODEV);
}