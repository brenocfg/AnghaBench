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
struct TYPE_12__ {int /*<<< orphan*/  FreeQlock; int /*<<< orphan*/  mfcnt; int /*<<< orphan*/  FreeQ; } ;
struct TYPE_10__ {int arg1; int /*<<< orphan*/  list; } ;
struct TYPE_8__ {TYPE_3__ linkage; } ;
struct TYPE_9__ {TYPE_1__ frame; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
typedef  TYPE_4__ MPT_FRAME_HDR ;
typedef  TYPE_5__ MPT_ADAPTER ;

/* Variables and functions */
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
mpt_free_msg_frame(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf)
{
	unsigned long flags;

	/*  Put Request back on FreeQ!  */
	spin_lock_irqsave(&ioc->FreeQlock, flags);
	if (cpu_to_le32(mf->u.frame.linkage.arg1) == 0xdeadbeaf)
		goto out;
	/* signature to know if this mf is freed */
	mf->u.frame.linkage.arg1 = cpu_to_le32(0xdeadbeaf);
	list_add_tail(&mf->u.frame.linkage.list, &ioc->FreeQ);
#ifdef MFCNT
	ioc->mfcnt--;
#endif
 out:
	spin_unlock_irqrestore(&ioc->FreeQlock, flags);
}