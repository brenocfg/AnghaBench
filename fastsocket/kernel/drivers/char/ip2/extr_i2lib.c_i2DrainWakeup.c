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
typedef  TYPE_2__* i2ChanStrPtr ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct TYPE_4__ {int /*<<< orphan*/  pBookmarkWait; TYPE_1__ BookmarkTimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANN ; 
 int /*<<< orphan*/  ITRC_DRAIN ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
i2DrainWakeup(unsigned long d)
{
	i2ChanStrPtr pCh = (i2ChanStrPtr)d;

	ip2trace (CHANN, ITRC_DRAIN, 10, 1, pCh->BookmarkTimer.expires );

	pCh->BookmarkTimer.expires = 0;
	wake_up_interruptible( &pCh->pBookmarkWait );
}