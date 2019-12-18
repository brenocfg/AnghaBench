#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_14__ {TYPE_3__* data; } ;
typedef  TYPE_2__ xfs_dabuf_t ;
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct TYPE_13__ {scalar_t__ pad; void* magic; scalar_t__ back; scalar_t__ forw; } ;
struct TYPE_12__ {void* level; scalar_t__ count; TYPE_1__ info; } ;
struct TYPE_15__ {TYPE_11__ hdr; } ;
typedef  TYPE_3__ xfs_da_intnode_t ;
struct TYPE_16__ {int /*<<< orphan*/  dp; int /*<<< orphan*/ * trans; } ;
typedef  TYPE_4__ xfs_da_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_DA_LOGRANGE (TYPE_3__*,TYPE_11__*,int) ; 
 int XFS_DA_NODE_MAGIC ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  trace_xfs_da_node_create (TYPE_4__*) ; 
 int xfs_da_get_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__**,int) ; 
 int /*<<< orphan*/  xfs_da_log_buf (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

int
xfs_da_node_create(xfs_da_args_t *args, xfs_dablk_t blkno, int level,
				 xfs_dabuf_t **bpp, int whichfork)
{
	xfs_da_intnode_t *node;
	xfs_dabuf_t *bp;
	int error;
	xfs_trans_t *tp;

	trace_xfs_da_node_create(args);

	tp = args->trans;
	error = xfs_da_get_buf(tp, args->dp, blkno, -1, &bp, whichfork);
	if (error)
		return(error);
	ASSERT(bp != NULL);
	node = bp->data;
	node->hdr.info.forw = 0;
	node->hdr.info.back = 0;
	node->hdr.info.magic = cpu_to_be16(XFS_DA_NODE_MAGIC);
	node->hdr.info.pad = 0;
	node->hdr.count = 0;
	node->hdr.level = cpu_to_be16(level);

	xfs_da_log_buf(tp, bp,
		XFS_DA_LOGRANGE(node, &node->hdr, sizeof(node->hdr)));

	*bpp = bp;
	return(0);
}