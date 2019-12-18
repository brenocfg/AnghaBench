#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct media_bay_info {int /*<<< orphan*/  timer; int /*<<< orphan*/  index; int /*<<< orphan*/  state; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* power ) (struct media_bay_info*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MBDBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MB_POWER_DELAY ; 
 int /*<<< orphan*/  mb_powering_down ; 
 int /*<<< orphan*/  mb_powering_up ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct media_bay_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct media_bay_info*,int) ; 

__attribute__((used)) static inline void set_mb_power(struct media_bay_info* bay, int onoff)
{
	/* Power up up and assert the bay reset line */
	if (onoff) {
		bay->ops->power(bay, 1);
		bay->state = mb_powering_up;
		MBDBG("mediabay%d: powering up\n", bay->index);
	} else { 
		/* Make sure everything is powered down & disabled */
		bay->ops->power(bay, 0);
		bay->state = mb_powering_down;
		MBDBG("mediabay%d: powering down\n", bay->index);
	}
	bay->timer = msecs_to_jiffies(MB_POWER_DELAY);
}