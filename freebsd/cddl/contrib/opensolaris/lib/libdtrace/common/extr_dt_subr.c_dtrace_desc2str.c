#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dtpd_id; char* dtpd_provider; char* dtpd_mod; char* dtpd_func; char* dtpd_name; } ;
typedef  TYPE_1__ dtrace_probedesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,scalar_t__,...) ; 

char *
dtrace_desc2str(const dtrace_probedesc_t *pdp, char *buf, size_t len)
{
	if (pdp->dtpd_id == 0) {
		(void) snprintf(buf, len, "%s:%s:%s:%s", pdp->dtpd_provider,
		    pdp->dtpd_mod, pdp->dtpd_func, pdp->dtpd_name);
	} else
		(void) snprintf(buf, len, "%u", pdp->dtpd_id);

	return (buf);
}