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
struct TYPE_3__ {char* dtpd_mod; char* dtpd_func; char* dtpd_name; } ;
typedef  TYPE_1__ dtrace_probedesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

__attribute__((used)) static char *
dt_probe_key(const dtrace_probedesc_t *pdp, char *s)
{
	(void) snprintf(s, INT_MAX, "%s:%s:%s",
	    pdp->dtpd_mod, pdp->dtpd_func, pdp->dtpd_name);
	return (s);
}