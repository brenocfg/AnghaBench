#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ usb_id; int /*<<< orphan*/  dev; } ;
struct snd_usb_caiaqdev {int* control_state; int* ep8_out_buf; TYPE_3__ chip; } ;
struct snd_usb_audio {int /*<<< orphan*/  card; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int CNT_INTVAL ; 
 unsigned char EP1_CMD_DIMM_LEDS ; 
 unsigned char EP1_CMD_WRITE_IO ; 
 scalar_t__ USB_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_PID_TRAKTORKONTROLS4 ; 
 int /*<<< orphan*/  USB_PID_TRAKTORKONTROLX1 ; 
 int /*<<< orphan*/  USB_VID_NATIVEINSTRUMENTS ; 
 struct snd_usb_caiaqdev* caiaqdev (int /*<<< orphan*/ ) ; 
 struct snd_usb_audio* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_usb_caiaq_send_command (struct snd_usb_caiaqdev*,unsigned char,int*,int) ; 
 int /*<<< orphan*/  usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int control_put(struct snd_kcontrol *kcontrol,
		       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_usb_audio *chip = snd_kcontrol_chip(kcontrol);
	struct snd_usb_caiaqdev *dev = caiaqdev(chip->card);
	int pos = kcontrol->private_value;
	int v = ucontrol->value.integer.value[0];
	unsigned char cmd = EP1_CMD_WRITE_IO;

	if (dev->chip.usb_id ==
		USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLX1))
		cmd = EP1_CMD_DIMM_LEDS;

	if (pos & CNT_INTVAL) {
		int i = pos & ~CNT_INTVAL;

		dev->control_state[i] = v;

		if (dev->chip.usb_id ==
			USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLS4)) {
			int actual_len;

			dev->ep8_out_buf[0] = i;
			dev->ep8_out_buf[1] = v;

			usb_bulk_msg(dev->chip.dev,
				     usb_sndbulkpipe(dev->chip.dev, 8),
				     dev->ep8_out_buf, sizeof(dev->ep8_out_buf),
				     &actual_len, 200);
		} else {
			snd_usb_caiaq_send_command(dev, cmd,
					dev->control_state, sizeof(dev->control_state));
		}
	} else {
		if (v)
			dev->control_state[pos / 8] |= 1 << (pos % 8);
		else
			dev->control_state[pos / 8] &= ~(1 << (pos % 8));

		snd_usb_caiaq_send_command(dev, cmd,
				dev->control_state, sizeof(dev->control_state));
	}

	return 1;
}