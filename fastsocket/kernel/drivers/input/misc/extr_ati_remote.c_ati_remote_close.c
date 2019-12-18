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
struct input_dev {int dummy; } ;
struct ati_remote {int /*<<< orphan*/  irq_urb; } ;

/* Variables and functions */
 struct ati_remote* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ati_remote_close(struct input_dev *inputdev)
{
	struct ati_remote *ati_remote = input_get_drvdata(inputdev);

	usb_kill_urb(ati_remote->irq_urb);
}