#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct nfsbuf* le_next; } ;
struct nfsbuf {scalar_t__ nb_np; int /*<<< orphan*/  nb_flags; int /*<<< orphan*/  nb_lblkno; TYPE_1__ nb_hash; } ;
typedef  scalar_t__ nfsnode_t ;
typedef  int /*<<< orphan*/  daddr64_t ;
struct TYPE_4__ {struct nfsbuf* lh_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSDBG (int,struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NB_INVAL ; 
 TYPE_2__* NFSBUFHASH (scalar_t__,int /*<<< orphan*/ ) ; 

struct nfsbuf *
nfs_buf_incore(nfsnode_t np, daddr64_t blkno)
{
	/* Search hash chain */
	struct nfsbuf * bp = NFSBUFHASH(np, blkno)->lh_first;
	for (; bp != NULL; bp = bp->nb_hash.le_next)
		if ((bp->nb_lblkno == blkno) && (bp->nb_np == np)) {
			if (!ISSET(bp->nb_flags, NB_INVAL)) {
				FSDBG(547, bp, blkno, bp->nb_flags, bp->nb_np);
				return (bp);
			}
		}
	return (NULL);
}