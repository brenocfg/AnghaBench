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
struct usb_device_id {int dummy; } ;
struct pvr2_context {void (* setup_func ) (struct pvr2_context*) ;int /*<<< orphan*/  hdw; struct pvr2_context* exist_next; struct pvr2_context* exist_prev; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PVR2_TRACE_CTXT ; 
 struct pvr2_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_context_destroy (struct pvr2_context*) ; 
 struct pvr2_context* pvr2_context_exist_first ; 
 struct pvr2_context* pvr2_context_exist_last ; 
 int /*<<< orphan*/  pvr2_context_mutex ; 
 int /*<<< orphan*/  pvr2_context_set_notify (struct pvr2_context*,int) ; 
 int /*<<< orphan*/  pvr2_hdw_create (struct usb_interface*,struct usb_device_id const*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_context*) ; 

struct pvr2_context *pvr2_context_create(
	struct usb_interface *intf,
	const struct usb_device_id *devid,
	void (*setup_func)(struct pvr2_context *))
{
	struct pvr2_context *mp = NULL;
	mp = kzalloc(sizeof(*mp),GFP_KERNEL);
	if (!mp) goto done;
	pvr2_trace(PVR2_TRACE_CTXT,"pvr2_context %p (create)",mp);
	mp->setup_func = setup_func;
	mutex_init(&mp->mutex);
	mutex_lock(&pvr2_context_mutex);
	mp->exist_prev = pvr2_context_exist_last;
	mp->exist_next = NULL;
	pvr2_context_exist_last = mp;
	if (mp->exist_prev) {
		mp->exist_prev->exist_next = mp;
	} else {
		pvr2_context_exist_first = mp;
	}
	mutex_unlock(&pvr2_context_mutex);
	mp->hdw = pvr2_hdw_create(intf,devid);
	if (!mp->hdw) {
		pvr2_context_destroy(mp);
		mp = NULL;
		goto done;
	}
	pvr2_context_set_notify(mp, !0);
 done:
	return mp;
}