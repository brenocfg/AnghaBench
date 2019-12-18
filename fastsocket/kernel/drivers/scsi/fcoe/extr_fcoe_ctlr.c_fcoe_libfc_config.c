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
struct libfc_function_template {int dummy; } ;
struct fcoe_ctlr {int /*<<< orphan*/  mode; } ;
struct fc_lport {int /*<<< orphan*/  tt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  fc_disc_init (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_elsct_init (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_exch_init (struct fc_lport*) ; 
 scalar_t__ fc_fcp_init (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_init (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_rport_init (struct fc_lport*) ; 
 int /*<<< orphan*/  fcoe_ctlr_mode_set (struct fc_lport*,struct fcoe_ctlr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct libfc_function_template const*,int) ; 

int fcoe_libfc_config(struct fc_lport *lport, struct fcoe_ctlr *fip,
		      const struct libfc_function_template *tt, int init_fcp)
{
	/* Set the function pointers set by the LLDD */
	memcpy(&lport->tt, tt, sizeof(*tt));
	if (init_fcp && fc_fcp_init(lport))
		return -ENOMEM;
	fc_exch_init(lport);
	fc_elsct_init(lport);
	fc_lport_init(lport);
	fc_rport_init(lport);
	fc_disc_init(lport);
	fcoe_ctlr_mode_set(lport, fip, fip->mode);
	return 0;
}