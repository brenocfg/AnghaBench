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
struct TYPE_4__ {int /*<<< orphan*/  end_jiffies; int /*<<< orphan*/  start_jiffies; } ;
struct TYPE_3__ {int dev_to_init; } ;
struct raid_set {TYPE_2__ recover; TYPE_1__ set; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearRSRecover (struct raid_set*) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void set_end_recovery(struct raid_set *rs)
{
	ClearRSRecover(rs);
/* Achtung: nicht mehr zurück setzten -> 'i' belibt in status output und userpace könnte sich darauf verlassen, das es verschiwndet!!!! */
	rs->set.dev_to_init = -1;

	/* Check for jiffies overrun. */
	rs->recover.end_jiffies = jiffies;
	if (rs->recover.end_jiffies < rs->recover.start_jiffies)
		rs->recover.end_jiffies = ~0;
}