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
struct uinput_request {int dummy; } ;
struct uinput_device {int /*<<< orphan*/  requests_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  uinput_request_alloc_id (struct uinput_device*,struct uinput_request*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int uinput_request_reserve_slot(struct uinput_device *udev, struct uinput_request *request)
{
	/* Allocate slot. If none are available right away, wait. */
	return wait_event_interruptible(udev->requests_waitq,
					!uinput_request_alloc_id(udev, request));
}