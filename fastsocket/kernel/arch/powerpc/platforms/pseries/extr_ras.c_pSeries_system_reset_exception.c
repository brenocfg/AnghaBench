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
struct rtas_error_log {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ fwnmi_active ; 
 struct rtas_error_log* fwnmi_get_errinfo (struct pt_regs*) ; 
 int /*<<< orphan*/  fwnmi_release_errinfo () ; 

int pSeries_system_reset_exception(struct pt_regs *regs)
{
	if (fwnmi_active) {
		struct rtas_error_log *errhdr = fwnmi_get_errinfo(regs);
		if (errhdr) {
			/* XXX Should look at FWNMI information */
		}
		fwnmi_release_errinfo();
	}
	return 0; /* need to perform reset */
}