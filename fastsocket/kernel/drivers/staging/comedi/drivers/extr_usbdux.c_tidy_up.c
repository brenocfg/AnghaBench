#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usbduxsub {int numOfInBuffers; int numOfOutBuffers; scalar_t__ pwm_cmd_running; scalar_t__ ao_cmd_running; scalar_t__ ai_cmd_running; TYPE_2__** dux_commands; TYPE_2__** dac_commands; TYPE_2__** inBuffer; TYPE_2__** insnBuffer; TYPE_2__* urbPwm; TYPE_2__** urbOut; TYPE_2__** urbIn; scalar_t__ probed; TYPE_1__* interface; } ;
struct TYPE_6__ {struct TYPE_6__** transfer_buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__**) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_set_intfdata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbduxsub_unlink_InURBs (struct usbduxsub*) ; 
 int /*<<< orphan*/  usbduxsub_unlink_OutURBs (struct usbduxsub*) ; 
 int /*<<< orphan*/  usbduxsub_unlink_PwmURBs (struct usbduxsub*) ; 

__attribute__((used)) static void tidy_up(struct usbduxsub *usbduxsub_tmp)
{
	int i;

	if (!usbduxsub_tmp)
		return;
	dev_dbg(&usbduxsub_tmp->interface->dev, "comedi_: tiding up\n");

	/* shows the usb subsystem that the driver is down */
	if (usbduxsub_tmp->interface)
		usb_set_intfdata(usbduxsub_tmp->interface, NULL);

	usbduxsub_tmp->probed = 0;

	if (usbduxsub_tmp->urbIn) {
		if (usbduxsub_tmp->ai_cmd_running) {
			usbduxsub_tmp->ai_cmd_running = 0;
			usbduxsub_unlink_InURBs(usbduxsub_tmp);
		}
		for (i = 0; i < usbduxsub_tmp->numOfInBuffers; i++) {
			kfree(usbduxsub_tmp->urbIn[i]->transfer_buffer);
			usbduxsub_tmp->urbIn[i]->transfer_buffer = NULL;
			usb_kill_urb(usbduxsub_tmp->urbIn[i]);
			usb_free_urb(usbduxsub_tmp->urbIn[i]);
			usbduxsub_tmp->urbIn[i] = NULL;
		}
		kfree(usbduxsub_tmp->urbIn);
		usbduxsub_tmp->urbIn = NULL;
	}
	if (usbduxsub_tmp->urbOut) {
		if (usbduxsub_tmp->ao_cmd_running) {
			usbduxsub_tmp->ao_cmd_running = 0;
			usbduxsub_unlink_OutURBs(usbduxsub_tmp);
		}
		for (i = 0; i < usbduxsub_tmp->numOfOutBuffers; i++) {
			if (usbduxsub_tmp->urbOut[i]->transfer_buffer) {
				kfree(usbduxsub_tmp->
				      urbOut[i]->transfer_buffer);
				usbduxsub_tmp->urbOut[i]->transfer_buffer =
				    NULL;
			}
			if (usbduxsub_tmp->urbOut[i]) {
				usb_kill_urb(usbduxsub_tmp->urbOut[i]);
				usb_free_urb(usbduxsub_tmp->urbOut[i]);
				usbduxsub_tmp->urbOut[i] = NULL;
			}
		}
		kfree(usbduxsub_tmp->urbOut);
		usbduxsub_tmp->urbOut = NULL;
	}
	if (usbduxsub_tmp->urbPwm) {
		if (usbduxsub_tmp->pwm_cmd_running) {
			usbduxsub_tmp->pwm_cmd_running = 0;
			usbduxsub_unlink_PwmURBs(usbduxsub_tmp);
		}
		kfree(usbduxsub_tmp->urbPwm->transfer_buffer);
		usbduxsub_tmp->urbPwm->transfer_buffer = NULL;
		usb_kill_urb(usbduxsub_tmp->urbPwm);
		usb_free_urb(usbduxsub_tmp->urbPwm);
		usbduxsub_tmp->urbPwm = NULL;
	}
	kfree(usbduxsub_tmp->inBuffer);
	usbduxsub_tmp->inBuffer = NULL;
	kfree(usbduxsub_tmp->insnBuffer);
	usbduxsub_tmp->insnBuffer = NULL;
	kfree(usbduxsub_tmp->inBuffer);
	usbduxsub_tmp->inBuffer = NULL;
	kfree(usbduxsub_tmp->dac_commands);
	usbduxsub_tmp->dac_commands = NULL;
	kfree(usbduxsub_tmp->dux_commands);
	usbduxsub_tmp->dux_commands = NULL;
	usbduxsub_tmp->ai_cmd_running = 0;
	usbduxsub_tmp->ao_cmd_running = 0;
	usbduxsub_tmp->pwm_cmd_running = 0;
}