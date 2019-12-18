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
struct usb_api_data {int done; int /*<<< orphan*/  wqh; } ;
struct urb {scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_api_blocking_completion(struct urb *urb)
{
        struct usb_api_data *awd = (struct usb_api_data *)urb->context;

	awd->done=1;
	wake_up(&awd->wqh);
}