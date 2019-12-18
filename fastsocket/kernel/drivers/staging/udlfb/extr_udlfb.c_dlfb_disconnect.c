#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct dlfb_data {TYPE_1__* info; struct dlfb_data* backing_buffer; int /*<<< orphan*/  screen_size; int /*<<< orphan*/  udev; int /*<<< orphan*/  tx_urb; int /*<<< orphan*/  bulk_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  screen_base; int /*<<< orphan*/  cmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct dlfb_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  rvfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct dlfb_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlfb_disconnect(struct usb_interface *interface)
{
	struct dlfb_data *dev_info = usb_get_intfdata(interface);

	mutex_unlock(&dev_info->bulk_mutex);

	usb_kill_urb(dev_info->tx_urb);
	usb_free_urb(dev_info->tx_urb);
	usb_set_intfdata(interface, NULL);
	usb_put_dev(dev_info->udev);

	if (dev_info->info) {
		unregister_framebuffer(dev_info->info);
		fb_dealloc_cmap(&dev_info->info->cmap);
		rvfree(dev_info->info->screen_base, dev_info->screen_size);
		kfree(dev_info->backing_buffer);
		framebuffer_release(dev_info->info);

	}

	kfree(dev_info);

	printk("DisplayLink device disconnected\n");
}