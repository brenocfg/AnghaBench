#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dtpd_id; } ;
typedef  TYPE_1__ dtrace_probedesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;

/* Variables and functions */
 scalar_t__ DTRACE_IDNONE ; 
 int /*<<< orphan*/  bcopy (TYPE_1__ const*,void*,int) ; 

__attribute__((used)) static int
dt_probe_desc(dtrace_hdl_t *dtp, const dtrace_probedesc_t *pdp, void *arg)
{
	if (((dtrace_probedesc_t *)arg)->dtpd_id == DTRACE_IDNONE) {
		bcopy(pdp, arg, sizeof (dtrace_probedesc_t));
		return (0);
	}

	return (1);
}