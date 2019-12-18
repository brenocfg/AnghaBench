#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_7__ {int /*<<< orphan*/  magic; } ;
struct TYPE_8__ {TYPE_1__ info; } ;
struct TYPE_9__ {TYPE_2__ hdr; } ;
typedef  TYPE_3__ xfs_dir2_leaf_t ;
struct TYPE_10__ {TYPE_3__* data; } ;
typedef  TYPE_4__ xfs_dabuf_t ;
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_da_log_buf (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_dir2_leaf_log_header(
	xfs_trans_t		*tp,		/* transaction pointer */
	xfs_dabuf_t		*bp)		/* leaf buffer */
{
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */

	leaf = bp->data;
	ASSERT(be16_to_cpu(leaf->hdr.info.magic) == XFS_DIR2_LEAF1_MAGIC ||
	       be16_to_cpu(leaf->hdr.info.magic) == XFS_DIR2_LEAFN_MAGIC);
	xfs_da_log_buf(tp, bp, (uint)((char *)&leaf->hdr - (char *)leaf),
		(uint)(sizeof(leaf->hdr) - 1));
}