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
struct snd_usb_audio {int /*<<< orphan*/  usb_id; int /*<<< orphan*/  shutdown; } ;
struct snd_info_entry {struct snd_usb_audio* private_data; } ;
struct snd_info_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ID_PRODUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_ID_VENDOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void proc_audio_usbid_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer)
{
	struct snd_usb_audio *chip = entry->private_data;
	if (!chip->shutdown)
		snd_iprintf(buffer, "%04x:%04x\n", 
			    USB_ID_VENDOR(chip->usb_id),
			    USB_ID_PRODUCT(chip->usb_id));
}