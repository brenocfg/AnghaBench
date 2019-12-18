#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  magic; } ;
struct TYPE_10__ {int /*<<< orphan*/  count; TYPE_1__ info; } ;
struct TYPE_11__ {TYPE_3__ hdr; TYPE_2__* ents; } ;
typedef  TYPE_4__ xfs_dir2_leaf_t ;
struct TYPE_12__ {TYPE_4__* data; } ;
typedef  TYPE_5__ xfs_dabuf_t ;
struct TYPE_9__ {int /*<<< orphan*/  hashval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_DIR2_LEAFN_MAGIC ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 

int						/* sort order */
xfs_dir2_leafn_order(
	xfs_dabuf_t	*leaf1_bp,		/* leaf1 buffer */
	xfs_dabuf_t	*leaf2_bp)		/* leaf2 buffer */
{
	xfs_dir2_leaf_t	*leaf1;			/* leaf1 structure */
	xfs_dir2_leaf_t	*leaf2;			/* leaf2 structure */

	leaf1 = leaf1_bp->data;
	leaf2 = leaf2_bp->data;
	ASSERT(be16_to_cpu(leaf1->hdr.info.magic) == XFS_DIR2_LEAFN_MAGIC);
	ASSERT(be16_to_cpu(leaf2->hdr.info.magic) == XFS_DIR2_LEAFN_MAGIC);
	if (be16_to_cpu(leaf1->hdr.count) > 0 &&
	    be16_to_cpu(leaf2->hdr.count) > 0 &&
	    (be32_to_cpu(leaf2->ents[0].hashval) < be32_to_cpu(leaf1->ents[0].hashval) ||
	     be32_to_cpu(leaf2->ents[be16_to_cpu(leaf2->hdr.count) - 1].hashval) <
	     be32_to_cpu(leaf1->ents[be16_to_cpu(leaf1->hdr.count) - 1].hashval)))
		return 1;
	return 0;
}