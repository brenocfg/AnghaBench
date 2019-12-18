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
struct hw {int /*<<< orphan*/  (* dao_set_spos ) (int /*<<< orphan*/ ,unsigned int) ;} ;
struct dao {int /*<<< orphan*/  ctrl_blk; scalar_t__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int dao_spdif_set_spos(struct dao *dao, unsigned int spos)
{
	((struct hw *)dao->hw)->dao_set_spos(dao->ctrl_blk, spos);
	return 0;
}