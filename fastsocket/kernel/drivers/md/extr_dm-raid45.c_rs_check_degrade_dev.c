#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stripe {scalar_t__ key; } ;
struct TYPE_10__ {int /*<<< orphan*/  ws_do_table_event; } ;
struct TYPE_8__ {unsigned int raid_devs; unsigned int ei; TYPE_1__* raid_type; int /*<<< orphan*/  failed_devs; } ;
struct raid_set {TYPE_4__ io; TYPE_5__* dev; TYPE_2__ set; } ;
struct TYPE_11__ {TYPE_3__* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_7__ {scalar_t__ parity_devs; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  DMERR (char*,...) ; 
 scalar_t__ DevFailed (TYPE_5__*) ; 
 int /*<<< orphan*/  SetRSProhibitWrites (struct raid_set*) ; 
 scalar_t__ TestSetDevFailed (TYPE_5__*) ; 
 int /*<<< orphan*/  TestSetRSDead (struct raid_set*) ; 
 int /*<<< orphan*/  TestSetRSDegraded (struct raid_set*) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_check_degrade_dev(struct raid_set *rs,
				 struct stripe *stripe, unsigned p)
{
	if (TestSetDevFailed(rs->dev + p))
		return;

	/* Through an event in case of member device errors. */
	if ((atomic_inc_return(&rs->set.failed_devs) >
	     rs->set.raid_type->parity_devs) &&
	     !TestSetRSDead(rs)) {
		/* Display RAID set dead message once. */
		unsigned p;
		char buf[BDEVNAME_SIZE];

		DMERR("FATAL: too many devices failed -> RAID set broken");
		for (p = 0; p < rs->set.raid_devs; p++) {
			if (DevFailed(rs->dev + p))
				DMERR("device /dev/%s failed",
				      bdevname(rs->dev[p].dev->bdev, buf));
		}
	}

	/* Only log the first member error. */
	if (!TestSetRSDegraded(rs)) {
		char buf[BDEVNAME_SIZE];

		/* Store index for recovery. */
		rs->set.ei = p;
		DMERR("CRITICAL: %sio error on device /dev/%s "
		      "in region=%llu; DEGRADING RAID set\n",
		      stripe ? "" : "FAKED ",
		      bdevname(rs->dev[p].dev->bdev, buf),
		      (unsigned long long) (stripe ? stripe->key : 0));
		DMERR("further device error messages suppressed");
	}

	/* Prohibit further writes to allow for userpace to update metadata. */
	SetRSProhibitWrites(rs);
	schedule_work(&rs->io.ws_do_table_event);
}