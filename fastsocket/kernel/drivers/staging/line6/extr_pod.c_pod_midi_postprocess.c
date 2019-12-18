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
struct usb_line6_pod {int /*<<< orphan*/  dumpreq; int /*<<< orphan*/  midi_postprocess; } ;

/* Variables and functions */
 unsigned char LINE6_CHANNEL_HOST ; 
 unsigned char LINE6_PARAM_CHANGE ; 
 unsigned char LINE6_PROGRAM_CHANGE ; 
 unsigned char POD_amp_model_setup ; 
 unsigned char POD_effect_setup ; 
 int /*<<< orphan*/  line6_invalidate_current (int /*<<< orphan*/ *) ; 

void pod_midi_postprocess(struct usb_line6_pod *pod, unsigned char *data, int length)
{
	int i;

	if (!pod->midi_postprocess)
		return;

	for (i = 0; i < length; ++i) {
		if (data[i] == (LINE6_PROGRAM_CHANGE | LINE6_CHANNEL_HOST)) {
			line6_invalidate_current(&pod->dumpreq);
			break;
		} else if ((data[i] == (LINE6_PARAM_CHANGE | LINE6_CHANNEL_HOST)) && (i < length - 1))
			if ((data[i + 1] == POD_amp_model_setup) || (data[i + 1] == POD_effect_setup)) {
				line6_invalidate_current(&pod->dumpreq);
				break;
			}
	}
}