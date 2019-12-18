#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_6__ {int /*<<< orphan*/  magic; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ xfs_dir2_free_t ;
typedef  int /*<<< orphan*/  xfs_dir2_free_hdr_t ;
struct TYPE_8__ {TYPE_2__* data; } ;
typedef  TYPE_3__ xfs_dabuf_t ;
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_FREE_MAGIC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_da_log_buf (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_dir2_free_log_header(
	xfs_trans_t		*tp,		/* transaction pointer */
	xfs_dabuf_t		*bp)		/* freespace buffer */
{
	xfs_dir2_free_t		*free;		/* freespace structure */

	free = bp->data;
	ASSERT(be32_to_cpu(free->hdr.magic) == XFS_DIR2_FREE_MAGIC);
	xfs_da_log_buf(tp, bp, (uint)((char *)&free->hdr - (char *)free),
		(uint)(sizeof(xfs_dir2_free_hdr_t) - 1));
}