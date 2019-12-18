#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* properties; struct snd_line6_pcm* line6pcm; } ;
struct usb_line6_pod {TYPE_2__ line6; int /*<<< orphan*/  firmware_version; scalar_t__ versionreq_ok; } ;
struct device {int dummy; } ;
struct usb_interface {struct device dev; } ;
struct snd_line6_pcm {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  device_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_channel ; 
 int /*<<< orphan*/  dev_attr_clip ; 
 int /*<<< orphan*/  dev_attr_device_id ; 
 int /*<<< orphan*/  dev_attr_dirty ; 
 int /*<<< orphan*/  dev_attr_dump ; 
 int /*<<< orphan*/  dev_attr_dump_buf ; 
 int /*<<< orphan*/  dev_attr_finish ; 
 int /*<<< orphan*/  dev_attr_firmware_version ; 
 int /*<<< orphan*/  dev_attr_midi_postprocess ; 
 int /*<<< orphan*/  dev_attr_monitor_level ; 
 int /*<<< orphan*/  dev_attr_name ; 
 int /*<<< orphan*/  dev_attr_name_buf ; 
 int /*<<< orphan*/  dev_attr_raw ; 
 int /*<<< orphan*/  dev_attr_retrieve_amp_setup ; 
 int /*<<< orphan*/  dev_attr_retrieve_channel ; 
 int /*<<< orphan*/  dev_attr_retrieve_effects_setup ; 
 int /*<<< orphan*/  dev_attr_routing ; 
 int /*<<< orphan*/  dev_attr_serial_number ; 
 int /*<<< orphan*/  dev_attr_store_amp_setup ; 
 int /*<<< orphan*/  dev_attr_store_channel ; 
 int /*<<< orphan*/  dev_attr_store_effects_setup ; 
 int /*<<< orphan*/  dev_attr_tuner_freq ; 
 int /*<<< orphan*/  dev_attr_tuner_mute ; 
 int /*<<< orphan*/  dev_attr_tuner_note ; 
 int /*<<< orphan*/  dev_attr_tuner_pitch ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pod_destruct (struct usb_interface*) ; 
 int /*<<< orphan*/  pod_remove_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  unlink_wait_clear_audio_in_urbs (struct snd_line6_pcm*) ; 
 int /*<<< orphan*/  unlink_wait_clear_audio_out_urbs (struct snd_line6_pcm*) ; 
 struct usb_line6_pod* usb_get_intfdata (struct usb_interface*) ; 

void pod_disconnect(struct usb_interface *interface)
{
	struct usb_line6_pod *pod;

	if (interface == NULL)
		return;
	pod = usb_get_intfdata(interface);

	if (pod != NULL) {
		struct snd_line6_pcm *line6pcm = pod->line6.line6pcm;
		struct device *dev = &interface->dev;

		if (line6pcm != NULL) {
			unlink_wait_clear_audio_out_urbs(line6pcm);
			unlink_wait_clear_audio_in_urbs(line6pcm);
		}

		if (dev != NULL) {
			/* remove sysfs entries: */
			if (pod->versionreq_ok)
				pod_remove_files(pod->firmware_version, pod->line6.properties->device_bit, dev);

			device_remove_file(dev, &dev_attr_channel);
			device_remove_file(dev, &dev_attr_clip);
			device_remove_file(dev, &dev_attr_device_id);
			device_remove_file(dev, &dev_attr_dirty);
			device_remove_file(dev, &dev_attr_dump);
			device_remove_file(dev, &dev_attr_dump_buf);
			device_remove_file(dev, &dev_attr_finish);
			device_remove_file(dev, &dev_attr_firmware_version);
			device_remove_file(dev, &dev_attr_midi_postprocess);
			device_remove_file(dev, &dev_attr_monitor_level);
			device_remove_file(dev, &dev_attr_name);
			device_remove_file(dev, &dev_attr_name_buf);
			device_remove_file(dev, &dev_attr_retrieve_amp_setup);
			device_remove_file(dev, &dev_attr_retrieve_channel);
			device_remove_file(dev, &dev_attr_retrieve_effects_setup);
			device_remove_file(dev, &dev_attr_routing);
			device_remove_file(dev, &dev_attr_serial_number);
			device_remove_file(dev, &dev_attr_store_amp_setup);
			device_remove_file(dev, &dev_attr_store_channel);
			device_remove_file(dev, &dev_attr_store_effects_setup);
			device_remove_file(dev, &dev_attr_tuner_freq);
			device_remove_file(dev, &dev_attr_tuner_mute);
			device_remove_file(dev, &dev_attr_tuner_note);
			device_remove_file(dev, &dev_attr_tuner_pitch);

#if CREATE_RAW_FILE
			device_remove_file(dev, &dev_attr_raw);
#endif
		}
	}

	pod_destruct(interface);
}