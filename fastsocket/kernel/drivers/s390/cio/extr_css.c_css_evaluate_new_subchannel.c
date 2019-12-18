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
struct subchannel_id {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct schib {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int css_probe_device (struct subchannel_id) ; 
 int /*<<< orphan*/  css_sch_is_valid (struct schib*) ; 
 scalar_t__ stsch_err (struct subchannel_id,struct schib*) ; 

__attribute__((used)) static int css_evaluate_new_subchannel(struct subchannel_id schid, int slow)
{
	struct schib schib;

	if (!slow) {
		/* Will be done on the slow path. */
		return -EAGAIN;
	}
	if (stsch_err(schid, &schib) || !css_sch_is_valid(&schib)) {
		/* Unusable - ignore. */
		return 0;
	}
	CIO_MSG_EVENT(4, "event: sch 0.%x.%04x, new\n", schid.ssid,
		      schid.sch_no);

	return css_probe_device(schid);
}