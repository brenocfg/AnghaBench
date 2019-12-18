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
struct sisusb_usb_data {struct sisusb_usb_data* SiS_Pr; int /*<<< orphan*/ * sisusb_dev; } ;
struct kref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  sisusb_free_buffers (struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  sisusb_free_urbs (struct sisusb_usb_data*) ; 
 struct sisusb_usb_data* to_sisusb_dev (struct kref*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ *) ; 

void
sisusb_delete(struct kref *kref)
{
	struct sisusb_usb_data *sisusb = to_sisusb_dev(kref);

	if (!sisusb)
		return;

	if (sisusb->sisusb_dev)
		usb_put_dev(sisusb->sisusb_dev);

	sisusb->sisusb_dev = NULL;
	sisusb_free_buffers(sisusb);
	sisusb_free_urbs(sisusb);
#ifdef INCL_SISUSB_CON
	kfree(sisusb->SiS_Pr);
#endif
	kfree(sisusb);
}