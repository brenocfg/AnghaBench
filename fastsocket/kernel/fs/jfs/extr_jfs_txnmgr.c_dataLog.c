#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tlock {int /*<<< orphan*/  flag; struct metapage* mp; int /*<<< orphan*/  ip; } ;
struct tblock {TYPE_3__* sb; } ;
struct metapage {int logical_size; int /*<<< orphan*/  index; scalar_t__ lid; } ;
struct TYPE_4__ {int /*<<< orphan*/  pxd; void* l2linesize; void* type; } ;
struct TYPE_5__ {TYPE_1__ redopage; } ;
struct lrd {int /*<<< orphan*/  backchain; void* type; TYPE_2__ log; } ;
struct jfs_log {int dummy; } ;
typedef  int /*<<< orphan*/  pxd_t ;
struct TYPE_6__ {int s_blocksize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2DATASLOTSIZE ; 
 int /*<<< orphan*/  LOG_DATA ; 
 int /*<<< orphan*/  LOG_REDOPAGE ; 
 int /*<<< orphan*/  PXDaddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PXDlength (int /*<<< orphan*/ *,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discard_metapage (struct metapage*) ; 
 int /*<<< orphan*/  grab_metapage (struct metapage*) ; 
 scalar_t__ jfs_dirtable_inline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmLog (struct jfs_log*,struct tblock*,struct lrd*,struct tlock*) ; 
 int /*<<< orphan*/  metapage_homeok (struct metapage*) ; 
 int /*<<< orphan*/  tlckWRITEPAGE ; 

__attribute__((used)) static int dataLog(struct jfs_log * log, struct tblock * tblk, struct lrd * lrd,
	    struct tlock * tlck)
{
	struct metapage *mp;
	pxd_t *pxd;

	mp = tlck->mp;

	/* initialize as REDOPAGE record format */
	lrd->log.redopage.type = cpu_to_le16(LOG_DATA);
	lrd->log.redopage.l2linesize = cpu_to_le16(L2DATASLOTSIZE);

	pxd = &lrd->log.redopage.pxd;

	/* log after-image for logredo(): */
	lrd->type = cpu_to_le16(LOG_REDOPAGE);

	if (jfs_dirtable_inline(tlck->ip)) {
		/*
		 * The table has been truncated, we've must have deleted
		 * the last entry, so don't bother logging this
		 */
		mp->lid = 0;
		grab_metapage(mp);
		metapage_homeok(mp);
		discard_metapage(mp);
		tlck->mp = NULL;
		return 0;
	}

	PXDaddress(pxd, mp->index);
	PXDlength(pxd, mp->logical_size >> tblk->sb->s_blocksize_bits);

	lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, tlck));

	/* mark page as homeward bound */
	tlck->flag |= tlckWRITEPAGE;

	return 0;
}