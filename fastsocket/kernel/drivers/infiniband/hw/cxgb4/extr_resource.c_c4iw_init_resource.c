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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tpt_table; int /*<<< orphan*/  qid_table; int /*<<< orphan*/  pdid_table; } ;
struct c4iw_rdev {TYPE_1__ resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  C4IW_ID_TABLE_F_RANDOM ; 
 int ENOMEM ; 
 int c4iw_id_table_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_id_table_free (int /*<<< orphan*/ *) ; 
 int c4iw_init_qid_table (struct c4iw_rdev*) ; 

int c4iw_init_resource(struct c4iw_rdev *rdev, u32 nr_tpt, u32 nr_pdid)
{
	int err = 0;
	err = c4iw_id_table_alloc(&rdev->resource.tpt_table, 0, nr_tpt, 1,
					C4IW_ID_TABLE_F_RANDOM);
	if (err)
		goto tpt_err;
	err = c4iw_init_qid_table(rdev);
	if (err)
		goto qid_err;
	err = c4iw_id_table_alloc(&rdev->resource.pdid_table, 0,
					nr_pdid, 1, 0);
	if (err)
		goto pdid_err;
	return 0;
 pdid_err:
	c4iw_id_table_free(&rdev->resource.qid_table);
 qid_err:
	c4iw_id_table_free(&rdev->resource.tpt_table);
 tpt_err:
	return -ENOMEM;
}