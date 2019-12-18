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
struct uinput_request {int id; } ;
struct uinput_device {int /*<<< orphan*/  requests_lock; struct uinput_request** requests; } ;

/* Variables and functions */
 int UINPUT_NUM_REQUESTS ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uinput_request_alloc_id(struct uinput_device *udev, struct uinput_request *request)
{
	int id;
	int err = -1;

	spin_lock(&udev->requests_lock);

	for (id = 0; id < UINPUT_NUM_REQUESTS; id++) {
		if (!udev->requests[id]) {
			request->id = id;
			udev->requests[id] = request;
			err = 0;
			break;
		}
	}

	spin_unlock(&udev->requests_lock);
	return err;
}