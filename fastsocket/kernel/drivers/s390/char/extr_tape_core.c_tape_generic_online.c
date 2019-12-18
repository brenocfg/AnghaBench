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
struct tape_discipline {int (* setup_device ) (struct tape_device*) ;int /*<<< orphan*/  owner; int /*<<< orphan*/  (* cleanup_device ) (struct tape_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct tape_device {scalar_t__ tape_state; scalar_t__ cdev_id; struct tape_discipline* discipline; TYPE_1__ lb_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_LH (int,char*,scalar_t__,...) ; 
 int EINVAL ; 
 scalar_t__ TS_INIT ; 
 int /*<<< orphan*/  TS_UNUSED ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int stub1 (struct tape_device*) ; 
 int /*<<< orphan*/  stub2 (struct tape_device*) ; 
 int tape_assign_minor (struct tape_device*) ; 
 int /*<<< orphan*/  tape_long_busy_timeout ; 
 int /*<<< orphan*/  tape_remove_minor (struct tape_device*) ; 
 int /*<<< orphan*/  tape_state_set (struct tape_device*,int /*<<< orphan*/ ) ; 
 int tapeblock_setup_device (struct tape_device*) ; 
 int /*<<< orphan*/  tapechar_cleanup_device (struct tape_device*) ; 
 int tapechar_setup_device (struct tape_device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int
tape_generic_online(struct tape_device *device,
		   struct tape_discipline *discipline)
{
	int rc;

	DBF_LH(6, "tape_enable_device(%p, %p)\n", device, discipline);

	if (device->tape_state != TS_INIT) {
		DBF_LH(3, "Tapestate not INIT (%d)\n", device->tape_state);
		return -EINVAL;
	}

	init_timer(&device->lb_timeout);
	device->lb_timeout.function = tape_long_busy_timeout;

	/* Let the discipline have a go at the device. */
	device->discipline = discipline;
	if (!try_module_get(discipline->owner)) {
		return -EINVAL;
	}

	rc = discipline->setup_device(device);
	if (rc)
		goto out;
	rc = tape_assign_minor(device);
	if (rc)
		goto out_discipline;

	rc = tapechar_setup_device(device);
	if (rc)
		goto out_minor;
	rc = tapeblock_setup_device(device);
	if (rc)
		goto out_char;

	tape_state_set(device, TS_UNUSED);

	DBF_LH(3, "(%08x): Drive set online\n", device->cdev_id);

	return 0;

out_char:
	tapechar_cleanup_device(device);
out_minor:
	tape_remove_minor(device);
out_discipline:
	device->discipline->cleanup_device(device);
	device->discipline = NULL;
out:
	module_put(discipline->owner);
	return rc;
}