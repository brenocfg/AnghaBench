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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  sb; int /*<<< orphan*/  org_name; } ;
typedef  TYPE_1__ ARCHD ;

/* Variables and functions */
 scalar_t__ PAX_DIR ; 
 int mk_link (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
cross_lnk(ARCHD *arcn)
{
	/*
	 * try to make a link to original file (-l flag in copy mode). make sure
	 * we do not try to link to directories in case we are running as root
	 * (and it might succeed).
	 */
	if (arcn->type == PAX_DIR)
		return(1);
	return(mk_link(arcn->org_name, &(arcn->sb), arcn->name, 1));
}