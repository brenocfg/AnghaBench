#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_audio_term {int id; int type; int /*<<< orphan*/  name; void* chconfig; int /*<<< orphan*/  channels; } ;
struct uac_selector_unit_descriptor {int* baSourceID; int bDescriptorSubtype; } ;
struct uac_processing_unit_descriptor {int* baSourceID; int bDescriptorSubtype; int /*<<< orphan*/  bNrInPins; } ;
struct uac_mixer_unit_descriptor {int bDescriptorSubtype; } ;
struct uac_input_terminal_descriptor {int /*<<< orphan*/  iTerminal; int /*<<< orphan*/  wChannelConfig; int /*<<< orphan*/  bNrChannels; int /*<<< orphan*/  wTerminalType; } ;
struct uac_feature_unit_descriptor {int bSourceID; } ;
struct uac_clock_source_descriptor {int bDescriptorSubtype; int /*<<< orphan*/  iClockSource; } ;
struct uac2_input_terminal_descriptor {int bCSourceID; int /*<<< orphan*/  iTerminal; int /*<<< orphan*/  bmChannelConfig; int /*<<< orphan*/  bNrChannels; int /*<<< orphan*/  wTerminalType; } ;
struct mixer_build {TYPE_1__* mixer; } ;
struct TYPE_2__ {int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int ENODEV ; 
#define  UAC1_EXTENSION_UNIT 135 
#define  UAC1_PROCESSING_UNIT 134 
#define  UAC2_CLOCK_SELECTOR 133 
#define  UAC2_CLOCK_SOURCE 132 
#define  UAC_FEATURE_UNIT 131 
#define  UAC_INPUT_TERMINAL 130 
#define  UAC_MIXER_UNIT 129 
#define  UAC_SELECTOR_UNIT 128 
 int /*<<< orphan*/  UAC_VERSION_1 ; 
 void* find_audio_control_unit (struct mixer_build*,int) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct usb_audio_term*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uac_mixer_unit_bNrChannels (struct uac_mixer_unit_descriptor*) ; 
 int /*<<< orphan*/  uac_mixer_unit_iMixer (struct uac_mixer_unit_descriptor*) ; 
 void* uac_mixer_unit_wChannelConfig (struct uac_mixer_unit_descriptor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uac_processing_unit_bNrChannels (struct uac_processing_unit_descriptor*) ; 
 int /*<<< orphan*/  uac_processing_unit_iProcessing (struct uac_processing_unit_descriptor*,int /*<<< orphan*/ ) ; 
 void* uac_processing_unit_wChannelConfig (struct uac_processing_unit_descriptor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uac_selector_unit_iSelector (struct uac_selector_unit_descriptor*) ; 

__attribute__((used)) static int check_input_term(struct mixer_build *state, int id, struct usb_audio_term *term)
{
	int err;
	void *p1;

	memset(term, 0, sizeof(*term));
	while ((p1 = find_audio_control_unit(state, id)) != NULL) {
		unsigned char *hdr = p1;
		term->id = id;
		switch (hdr[2]) {
		case UAC_INPUT_TERMINAL:
			if (state->mixer->protocol == UAC_VERSION_1) {
				struct uac_input_terminal_descriptor *d = p1;
				term->type = le16_to_cpu(d->wTerminalType);
				term->channels = d->bNrChannels;
				term->chconfig = le16_to_cpu(d->wChannelConfig);
				term->name = d->iTerminal;
			} else { /* UAC_VERSION_2 */
				struct uac2_input_terminal_descriptor *d = p1;
				term->type = le16_to_cpu(d->wTerminalType);
				term->channels = d->bNrChannels;
				term->chconfig = le32_to_cpu(d->bmChannelConfig);
				term->name = d->iTerminal;

				/* call recursively to get the clock selectors */
				err = check_input_term(state, d->bCSourceID, term);
				if (err < 0)
					return err;
			}
			return 0;
		case UAC_FEATURE_UNIT: {
			/* the header is the same for v1 and v2 */
			struct uac_feature_unit_descriptor *d = p1;
			id = d->bSourceID;
			break; /* continue to parse */
		}
		case UAC_MIXER_UNIT: {
			struct uac_mixer_unit_descriptor *d = p1;
			term->type = d->bDescriptorSubtype << 16; /* virtual type */
			term->channels = uac_mixer_unit_bNrChannels(d);
			term->chconfig = uac_mixer_unit_wChannelConfig(d, state->mixer->protocol);
			term->name = uac_mixer_unit_iMixer(d);
			return 0;
		}
		case UAC_SELECTOR_UNIT:
		case UAC2_CLOCK_SELECTOR: {
			struct uac_selector_unit_descriptor *d = p1;
			/* call recursively to retrieve the channel info */
			if (check_input_term(state, d->baSourceID[0], term) < 0)
				return -ENODEV;
			term->type = d->bDescriptorSubtype << 16; /* virtual type */
			term->id = id;
			term->name = uac_selector_unit_iSelector(d);
			return 0;
		}
		case UAC1_PROCESSING_UNIT:
		case UAC1_EXTENSION_UNIT: {
			struct uac_processing_unit_descriptor *d = p1;
			if (d->bNrInPins) {
				id = d->baSourceID[0];
				break; /* continue to parse */
			}
			term->type = d->bDescriptorSubtype << 16; /* virtual type */
			term->channels = uac_processing_unit_bNrChannels(d);
			term->chconfig = uac_processing_unit_wChannelConfig(d, state->mixer->protocol);
			term->name = uac_processing_unit_iProcessing(d, state->mixer->protocol);
			return 0;
		}
		case UAC2_CLOCK_SOURCE: {
			struct uac_clock_source_descriptor *d = p1;
			term->type = d->bDescriptorSubtype << 16; /* virtual type */
			term->id = id;
			term->name = d->iClockSource;
			return 0;
		}
		default:
			return -ENODEV;
		}
	}
	return -ENODEV;
}