#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tape_device {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,struct tape_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 

struct tape_device *
tape_get_device_reference(struct tape_device *device)
{
	DBF_EVENT(4, "tape_get_device_reference(%p) = %i\n", device,
		atomic_inc_return(&device->ref_count));

	return device;
}