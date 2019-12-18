#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  qid_table; } ;
struct TYPE_7__ {TYPE_2__* vr; } ;
struct c4iw_rdev {int qpmask; TYPE_4__ resource; TYPE_3__ lldi; } ;
struct TYPE_5__ {int start; int size; } ;
struct TYPE_6__ {TYPE_1__ qp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  c4iw_id_free (int /*<<< orphan*/ *,int) ; 
 scalar_t__ c4iw_id_table_alloc (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int c4iw_init_qid_table(struct c4iw_rdev *rdev)
{
	u32 i;

	if (c4iw_id_table_alloc(&rdev->resource.qid_table,
				rdev->lldi.vr->qp.start,
				rdev->lldi.vr->qp.size,
				rdev->lldi.vr->qp.size, 0))
		return -ENOMEM;

	for (i = rdev->lldi.vr->qp.start;
		i < rdev->lldi.vr->qp.start + rdev->lldi.vr->qp.size; i++)
		if (!(i & rdev->qpmask))
			c4iw_id_free(&rdev->resource.qid_table, i);
	return 0;
}