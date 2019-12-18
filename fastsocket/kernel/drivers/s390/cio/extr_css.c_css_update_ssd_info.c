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
struct TYPE_2__ {int /*<<< orphan*/  pmcw; } ;
struct subchannel {int /*<<< orphan*/  ssd_info; TYPE_1__ schib; int /*<<< orphan*/  schid; } ;

/* Variables and functions */
 int chsc_get_ssd_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cio_is_console (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssd_from_pmcw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssd_register_chpids (int /*<<< orphan*/ *) ; 

void css_update_ssd_info(struct subchannel *sch)
{
	int ret;

	if (cio_is_console(sch->schid)) {
		/* Console is initialized too early for functions requiring
		 * memory allocation. */
		ssd_from_pmcw(&sch->ssd_info, &sch->schib.pmcw);
	} else {
		ret = chsc_get_ssd_info(sch->schid, &sch->ssd_info);
		if (ret)
			ssd_from_pmcw(&sch->ssd_info, &sch->schib.pmcw);
		ssd_register_chpids(&sch->ssd_info);
	}
}