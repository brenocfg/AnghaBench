#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hw {int /*<<< orphan*/  (* dao_commit_write ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct dao {int /*<<< orphan*/  ctrl_blk; scalar_t__ hw; TYPE_1__ daio; } ;

/* Variables and functions */
 int /*<<< orphan*/  daio_device_index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dao_commit_write(struct dao *dao)
{
	((struct hw *)dao->hw)->dao_commit_write(dao->hw,
		daio_device_index(dao->daio.type, dao->hw), dao->ctrl_blk);
	return 0;
}