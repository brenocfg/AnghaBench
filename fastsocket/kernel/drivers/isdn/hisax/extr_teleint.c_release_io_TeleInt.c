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
struct TYPE_3__ {scalar_t__ addr; int /*<<< orphan*/  timer; } ;
struct TYPE_4__ {TYPE_1__ hfc; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  releasehfc (struct IsdnCardState*) ; 

__attribute__((used)) static void
release_io_TeleInt(struct IsdnCardState *cs)
{
	del_timer(&cs->hw.hfc.timer);
	releasehfc(cs);
	if (cs->hw.hfc.addr)
		release_region(cs->hw.hfc.addr, 2);
}