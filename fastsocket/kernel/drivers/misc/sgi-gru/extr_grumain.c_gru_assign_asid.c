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
struct gru_state {int gs_asid; int gs_asid_limit; int /*<<< orphan*/  gs_gid; } ;

/* Variables and functions */
 scalar_t__ ASID_INC ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int gru_reset_asid_limit (struct gru_state*,int) ; 
 int /*<<< orphan*/  grudev ; 

__attribute__((used)) static int gru_assign_asid(struct gru_state *gru)
{
	int asid;

	gru->gs_asid += ASID_INC;
	asid = gru->gs_asid;
	if (asid >= gru->gs_asid_limit)
		asid = gru_reset_asid_limit(gru, asid);

	gru_dbg(grudev, "gid %d, asid 0x%x\n", gru->gs_gid, asid);
	return asid;
}