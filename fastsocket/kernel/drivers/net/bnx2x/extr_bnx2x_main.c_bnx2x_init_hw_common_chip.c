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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_NOMCP (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x__common_init_phy (struct bnx2x*) ; 
 int bnx2x_init_hw_common (struct bnx2x*) ; 

__attribute__((used)) static int bnx2x_init_hw_common_chip(struct bnx2x *bp)
{
	int rc = bnx2x_init_hw_common(bp);

	if (rc)
		return rc;

	/* In E2 2-PORT mode, same ext phy is used for the two paths */
	if (!BP_NOMCP(bp))
		bnx2x__common_init_phy(bp);

	return 0;
}