#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t lid_t ;
struct TYPE_8__ {size_t freelock; scalar_t__ tlocksInUse; int /*<<< orphan*/  freelockwait; } ;
struct TYPE_7__ {size_t next; } ;
struct TYPE_6__ {int /*<<< orphan*/  txLockAlloc_freelock; int /*<<< orphan*/  txLockAlloc; } ;
struct TYPE_5__ {int /*<<< orphan*/  maxlid; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIGHWATERMARK (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXN_SLEEP (int /*<<< orphan*/ *) ; 
 TYPE_4__ TxAnchor ; 
 TYPE_3__* TxLock ; 
 scalar_t__ TxLockHWM ; 
 TYPE_2__ TxStat ; 
 int /*<<< orphan*/  jfsSyncThread ; 
 int /*<<< orphan*/  jfs_info (char*) ; 
 int jfs_tlocks_low ; 
 TYPE_1__ stattx ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static lid_t txLockAlloc(void)
{
	lid_t lid;

	INCREMENT(TxStat.txLockAlloc);
	if (!TxAnchor.freelock) {
		INCREMENT(TxStat.txLockAlloc_freelock);
	}

	while (!(lid = TxAnchor.freelock))
		TXN_SLEEP(&TxAnchor.freelockwait);
	TxAnchor.freelock = TxLock[lid].next;
	HIGHWATERMARK(stattx.maxlid, lid);
	if ((++TxAnchor.tlocksInUse > TxLockHWM) && (jfs_tlocks_low == 0)) {
		jfs_info("txLockAlloc tlocks low");
		jfs_tlocks_low = 1;
		wake_up_process(jfsSyncThread);
	}

	return lid;
}