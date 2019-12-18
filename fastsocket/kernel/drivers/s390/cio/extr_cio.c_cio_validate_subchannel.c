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
struct subchannel_id {int sch_no; int /*<<< orphan*/  ssid; } ;
struct TYPE_3__ {int st; } ;
struct TYPE_4__ {TYPE_1__ pmcw; } ;
struct subchannel {int st; int /*<<< orphan*/ * lock; struct subchannel_id schid; TYPE_2__ schib; int /*<<< orphan*/  reg_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int ENXIO ; 
#define  SUBCHANNEL_TYPE_IO 129 
#define  SUBCHANNEL_TYPE_MSG 128 
 int cio_create_sch_lock (struct subchannel*) ; 
 int /*<<< orphan*/ * cio_get_console_lock () ; 
 scalar_t__ cio_is_console (struct subchannel_id) ; 
 int cio_validate_io_subchannel (struct subchannel*) ; 
 int cio_validate_msg_subchannel (struct subchannel*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct subchannel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int stsch_err (struct subchannel_id,TYPE_2__*) ; 

int cio_validate_subchannel(struct subchannel *sch, struct subchannel_id schid)
{
	char dbf_txt[15];
	int ccode;
	int err;

	sprintf(dbf_txt, "valsch%x", schid.sch_no);
	CIO_TRACE_EVENT(4, dbf_txt);

	/* Nuke all fields. */
	memset(sch, 0, sizeof(struct subchannel));

	sch->schid = schid;
	if (cio_is_console(schid)) {
		sch->lock = cio_get_console_lock();
	} else {
		err = cio_create_sch_lock(sch);
		if (err)
			goto out;
	}
	mutex_init(&sch->reg_mutex);

	/*
	 * The first subchannel that is not-operational (ccode==3)
	 *  indicates that there aren't any more devices available.
	 * If stsch gets an exception, it means the current subchannel set
	 *  is not valid.
	 */
	ccode = stsch_err (schid, &sch->schib);
	if (ccode) {
		err = (ccode == 3) ? -ENXIO : ccode;
		goto out;
	}
	/* Copy subchannel type from path management control word. */
	sch->st = sch->schib.pmcw.st;

	switch (sch->st) {
	case SUBCHANNEL_TYPE_IO:
		err = cio_validate_io_subchannel(sch);
		break;
	case SUBCHANNEL_TYPE_MSG:
		err = cio_validate_msg_subchannel(sch);
		break;
	default:
		err = 0;
	}
	if (err)
		goto out;

	CIO_MSG_EVENT(4, "Subchannel 0.%x.%04x reports subchannel type %04X\n",
		      sch->schid.ssid, sch->schid.sch_no, sch->st);
	return 0;
out:
	if (!cio_is_console(schid))
		kfree(sch->lock);
	sch->lock = NULL;
	return err;
}