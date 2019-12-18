#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dtpd_name; int /*<<< orphan*/  dtpd_func; int /*<<< orphan*/  dtpd_mod; int /*<<< orphan*/  dtpd_provider; int /*<<< orphan*/  dtpd_id; } ;
typedef  TYPE_2__ dtrace_probedesc_t ;
struct TYPE_9__ {int /*<<< orphan*/  dtpr_name; int /*<<< orphan*/  dtpr_func; int /*<<< orphan*/  dtpr_mod; TYPE_1__* dtpr_provider; int /*<<< orphan*/  dtpr_id; } ;
typedef  TYPE_3__ dtrace_probe_t ;
struct TYPE_7__ {int /*<<< orphan*/  dtpv_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_FUNCNAMELEN ; 
 int /*<<< orphan*/  DTRACE_MODNAMELEN ; 
 int /*<<< orphan*/  DTRACE_NAMELEN ; 
 int /*<<< orphan*/  DTRACE_PROVNAMELEN ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_probe_description(const dtrace_probe_t *prp, dtrace_probedesc_t *pdp)
{
	bzero(pdp, sizeof (dtrace_probedesc_t));
	pdp->dtpd_id = prp->dtpr_id;

	/* APPLE NOTE: Darwin employs size bounded string operation. */
	(void) strlcpy(pdp->dtpd_provider,
	    prp->dtpr_provider->dtpv_name, DTRACE_PROVNAMELEN);

	(void) strlcpy(pdp->dtpd_mod, prp->dtpr_mod, DTRACE_MODNAMELEN);
	(void) strlcpy(pdp->dtpd_func, prp->dtpr_func, DTRACE_FUNCNAMELEN);
	(void) strlcpy(pdp->dtpd_name, prp->dtpr_name, DTRACE_NAMELEN);
}