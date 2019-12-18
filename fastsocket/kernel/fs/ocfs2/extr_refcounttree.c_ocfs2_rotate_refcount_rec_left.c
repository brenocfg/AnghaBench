#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_refcount_rec {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  rl_used; TYPE_2__* rl_recs; } ;
struct ocfs2_refcount_block {TYPE_1__ rf_records; } ;
struct TYPE_6__ {scalar_t__ r_refcount; int /*<<< orphan*/  r_clusters; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ocfs2_rotate_refcount_rec_left(struct ocfs2_refcount_block *rb,
					   int index)
{
	BUG_ON(rb->rf_records.rl_recs[index].r_refcount !=
	       rb->rf_records.rl_recs[index+1].r_refcount);

	le32_add_cpu(&rb->rf_records.rl_recs[index].r_clusters,
		     le32_to_cpu(rb->rf_records.rl_recs[index+1].r_clusters));

	if (index < le16_to_cpu(rb->rf_records.rl_used) - 2)
		memmove(&rb->rf_records.rl_recs[index + 1],
			&rb->rf_records.rl_recs[index + 2],
			sizeof(struct ocfs2_refcount_rec) *
			(le16_to_cpu(rb->rf_records.rl_used) - index - 2));

	memset(&rb->rf_records.rl_recs[le16_to_cpu(rb->rf_records.rl_used) - 1],
	       0, sizeof(struct ocfs2_refcount_rec));
	le16_add_cpu(&rb->rf_records.rl_used, -1);
}