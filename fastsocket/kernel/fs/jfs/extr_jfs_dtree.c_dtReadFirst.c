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
struct metapage {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btstack {struct btframe* top; } ;
struct btframe {struct metapage* mp; scalar_t__ index; scalar_t__ bn; } ;
typedef  size_t s8 ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  pxd_t ;
struct TYPE_6__ {int flag; } ;
struct TYPE_7__ {int /*<<< orphan*/ * slot; TYPE_1__ header; } ;
typedef  TYPE_2__ dtpage_t ;
struct TYPE_8__ {int l2bsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CLR (struct btstack*) ; 
 int BT_LEAF ; 
 int /*<<< orphan*/  BT_PUSH (struct btstack*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_STACK_DUMP (struct btstack*) ; 
 scalar_t__ BT_STACK_FULL (struct btstack*) ; 
 int /*<<< orphan*/  DT_GETPAGE (struct inode*,scalar_t__,struct metapage*,int,TYPE_2__*,int) ; 
 size_t* DT_GETSTBL (TYPE_2__*) ; 
 int /*<<< orphan*/  DT_PUTPAGE (struct metapage*) ; 
 int EIO ; 
 TYPE_3__* JFS_SBI (int /*<<< orphan*/ ) ; 
 scalar_t__ addressPXD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int lengthPXD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dtReadFirst(struct inode *ip, struct btstack * btstack)
{
	int rc = 0;
	s64 bn;
	int psize = 288;	/* initial in-line directory */
	struct metapage *mp;
	dtpage_t *p;
	s8 *stbl;
	struct btframe *btsp;
	pxd_t *xd;

	BT_CLR(btstack);	/* reset stack */

	/*
	 *	descend leftmost path of the tree
	 *
	 * by convention, root bn = 0.
	 */
	for (bn = 0;;) {
		DT_GETPAGE(ip, bn, mp, psize, p, rc);
		if (rc)
			return rc;

		/*
		 * leftmost leaf page
		 */
		if (p->header.flag & BT_LEAF) {
			/* return leftmost entry */
			btsp = btstack->top;
			btsp->bn = bn;
			btsp->index = 0;
			btsp->mp = mp;

			return 0;
		}

		/*
		 * descend down to leftmost child page
		 */
		if (BT_STACK_FULL(btstack)) {
			DT_PUTPAGE(mp);
			jfs_error(ip->i_sb, "dtReadFirst: btstack overrun");
			BT_STACK_DUMP(btstack);
			return -EIO;
		}
		/* push (bn, index) of the parent page/entry */
		BT_PUSH(btstack, bn, 0);

		/* get the leftmost entry */
		stbl = DT_GETSTBL(p);
		xd = (pxd_t *) & p->slot[stbl[0]];

		/* get the child page block address */
		bn = addressPXD(xd);
		psize = lengthPXD(xd) << JFS_SBI(ip->i_sb)->l2bsize;

		/* unpin the parent page */
		DT_PUTPAGE(mp);
	}
}