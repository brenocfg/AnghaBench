#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_10__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_2__ xfs_dir2_data_unused_t ;
struct TYPE_9__ {int /*<<< orphan*/  magic; } ;
struct TYPE_11__ {TYPE_1__ hdr; } ;
typedef  TYPE_3__ xfs_dir2_data_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_off_t ;
struct TYPE_12__ {TYPE_3__* data; } ;
typedef  TYPE_4__ xfs_dabuf_t ;
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_BLOCK_MAGIC ; 
 scalar_t__ XFS_DIR2_DATA_MAGIC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_da_log_buf (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_dir2_data_unused_tag_p (TYPE_2__*) ; 

void
xfs_dir2_data_log_unused(
	xfs_trans_t		*tp,		/* transaction pointer */
	xfs_dabuf_t		*bp,		/* block buffer */
	xfs_dir2_data_unused_t	*dup)		/* data unused pointer */
{
	xfs_dir2_data_t		*d;		/* data block pointer */

	d = bp->data;
	ASSERT(be32_to_cpu(d->hdr.magic) == XFS_DIR2_DATA_MAGIC ||
	       be32_to_cpu(d->hdr.magic) == XFS_DIR2_BLOCK_MAGIC);
	/*
	 * Log the first part of the unused entry.
	 */
	xfs_da_log_buf(tp, bp, (uint)((char *)dup - (char *)d),
		(uint)((char *)&dup->length + sizeof(dup->length) -
		       1 - (char *)d));
	/*
	 * Log the end (tag) of the unused entry.
	 */
	xfs_da_log_buf(tp, bp,
		(uint)((char *)xfs_dir2_data_unused_tag_p(dup) - (char *)d),
		(uint)((char *)xfs_dir2_data_unused_tag_p(dup) - (char *)d +
		       sizeof(xfs_dir2_data_off_t) - 1));
}