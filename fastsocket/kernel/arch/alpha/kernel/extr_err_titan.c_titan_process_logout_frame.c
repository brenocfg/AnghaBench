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
struct el_common {scalar_t__ sys_offset; } ;
struct el_TITAN_sysdata_mcheck {int /*<<< orphan*/  p1_agperror; int /*<<< orphan*/  p1_aperror; int /*<<< orphan*/  p1_gperror; int /*<<< orphan*/  p1_serror; int /*<<< orphan*/  p0_agperror; int /*<<< orphan*/  p0_aperror; int /*<<< orphan*/  p0_gperror; int /*<<< orphan*/  p0_serror; int /*<<< orphan*/  c_misc; } ;

/* Variables and functions */
 int MCHK_DISPOSITION_UNKNOWN_ERROR ; 
 int titan_parse_c_misc (int /*<<< orphan*/ ,int) ; 
 int titan_parse_p_chip (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
titan_process_logout_frame(struct el_common *mchk_header, int print)
{
	struct el_TITAN_sysdata_mcheck *tmchk =
		(struct el_TITAN_sysdata_mcheck *)
		((unsigned long)mchk_header + mchk_header->sys_offset);
	int status = MCHK_DISPOSITION_UNKNOWN_ERROR;

	status |= titan_parse_c_misc(tmchk->c_misc, print);
	status |= titan_parse_p_chip(0, tmchk->p0_serror, tmchk->p0_gperror,
				     tmchk->p0_aperror, tmchk->p0_agperror, 
				     print);
	status |= titan_parse_p_chip(1, tmchk->p1_serror, tmchk->p1_gperror,
				     tmchk->p1_aperror, tmchk->p1_agperror, 
				     print);

	return status;
}