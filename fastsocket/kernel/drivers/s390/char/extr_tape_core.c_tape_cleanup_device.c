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
struct tape_device {TYPE_1__* discipline; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* cleanup_device ) (struct tape_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MS_UNKNOWN ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tape_device*) ; 
 int /*<<< orphan*/  tape_med_state_set (struct tape_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_remove_minor (struct tape_device*) ; 
 int /*<<< orphan*/  tapeblock_cleanup_device (struct tape_device*) ; 
 int /*<<< orphan*/  tapechar_cleanup_device (struct tape_device*) ; 

__attribute__((used)) static void
tape_cleanup_device(struct tape_device *device)
{
	tapeblock_cleanup_device(device);
	tapechar_cleanup_device(device);
	device->discipline->cleanup_device(device);
	module_put(device->discipline->owner);
	tape_remove_minor(device);
	tape_med_state_set(device, MS_UNKNOWN);
}