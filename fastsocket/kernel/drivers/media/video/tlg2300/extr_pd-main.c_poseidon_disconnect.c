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
struct poseidon {int /*<<< orphan*/  kref; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  dvb_data; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  POSEIDON_STATE_DISCONNECT ; 
 int /*<<< orphan*/  dvb_stop_streaming (int /*<<< orphan*/ *) ; 
 struct poseidon* get_pd (struct usb_interface*) ; 
 scalar_t__ in_hibernation (struct poseidon*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logpm (struct poseidon*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_dvb_usb_device_exit (struct poseidon*) ; 
 int /*<<< orphan*/  pd_video_exit (struct poseidon*) ; 
 int /*<<< orphan*/  poseidon_audio_free (struct poseidon*) ; 
 int /*<<< orphan*/  poseidon_delete ; 
 int /*<<< orphan*/  poseidon_fm_exit (struct poseidon*) ; 
 int /*<<< orphan*/  stop_all_video_stream (struct poseidon*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void poseidon_disconnect(struct usb_interface *interface)
{
	struct poseidon *pd = get_pd(interface);

	if (!pd)
		return;
	logpm(pd);
	if (in_hibernation(pd))
		return;

	mutex_lock(&pd->lock);
	pd->state |= POSEIDON_STATE_DISCONNECT;
	mutex_unlock(&pd->lock);

	/* stop urb transferring */
	stop_all_video_stream(pd);
	dvb_stop_streaming(&pd->dvb_data);

	/*unregister v4l2 device */
	v4l2_device_unregister(&pd->v4l2_dev);

	pd_dvb_usb_device_exit(pd);
	poseidon_fm_exit(pd);

	poseidon_audio_free(pd);
	pd_video_exit(pd);

	usb_set_intfdata(interface, NULL);
	kref_put(&pd->kref, poseidon_delete);
}