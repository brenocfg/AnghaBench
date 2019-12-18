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
struct usb_interface {int dummy; } ;
struct ua101 {int /*<<< orphan*/  mutex; struct usb_interface** intf; int /*<<< orphan*/  playback; int /*<<< orphan*/  capture; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct usb_interface**) ; 
 int /*<<< orphan*/  free_stream_buffers (struct ua101*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_stream_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ua101_driver ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_usb_related_resources(struct ua101 *ua,
				       struct usb_interface *interface)
{
	unsigned int i;
	struct usb_interface *intf;

	mutex_lock(&ua->mutex);
	free_stream_urbs(&ua->capture);
	free_stream_urbs(&ua->playback);
	mutex_unlock(&ua->mutex);
	free_stream_buffers(ua, &ua->capture);
	free_stream_buffers(ua, &ua->playback);

	for (i = 0; i < ARRAY_SIZE(ua->intf); ++i) {
		mutex_lock(&ua->mutex);
		intf = ua->intf[i];
		ua->intf[i] = NULL;
		mutex_unlock(&ua->mutex);
		if (intf) {
			usb_set_intfdata(intf, NULL);
			if (intf != interface)
				usb_driver_release_interface(&ua101_driver,
							     intf);
		}
	}
}