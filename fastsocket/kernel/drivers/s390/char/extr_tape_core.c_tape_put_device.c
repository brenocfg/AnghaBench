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
struct tape_device {struct tape_device* modeset_byte; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,...) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tape_device*) ; 

struct tape_device *
tape_put_device(struct tape_device *device)
{
	int remain;

	remain = atomic_dec_return(&device->ref_count);
	if (remain > 0) {
		DBF_EVENT(4, "tape_put_device(%p) -> %i\n", device, remain);
	} else {
		if (remain < 0) {
			DBF_EVENT(4, "put device without reference\n");
		} else {
			DBF_EVENT(4, "tape_free_device(%p)\n", device);
			kfree(device->modeset_byte);
			kfree(device);
		}
	}

	return NULL;			
}