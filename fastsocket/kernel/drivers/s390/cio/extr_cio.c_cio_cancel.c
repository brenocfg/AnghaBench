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
struct subchannel {int /*<<< orphan*/  schid; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ccode ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_HEX_EVENT (int,int*,int) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  cio_update_schib (struct subchannel*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int xsch (int /*<<< orphan*/ ) ; 

int
cio_cancel (struct subchannel *sch)
{
	int ccode;

	if (!sch)
		return -ENODEV;

	CIO_TRACE_EVENT(2, "cancelIO");
	CIO_TRACE_EVENT(2, dev_name(&sch->dev));

	ccode = xsch (sch->schid);

	CIO_HEX_EVENT(2, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:		/* success */
		/* Update information in scsw. */
		if (cio_update_schib(sch))
			return -ENODEV;
		return 0;
	case 1:		/* status pending */
		return -EBUSY;
	case 2:		/* not applicable */
		return -EINVAL;
	default:	/* not oper */
		return -ENODEV;
	}
}