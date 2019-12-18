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
struct usbmix_ctl_map {scalar_t__ id; int /*<<< orphan*/  ignore_ctl_error; int /*<<< orphan*/  selector_map; int /*<<< orphan*/  map; } ;
struct usb_mixer_interface {scalar_t__ protocol; TYPE_2__* hostif; int /*<<< orphan*/  ignore_ctl_error; TYPE_1__* chip; } ;
struct uac2_output_terminal_descriptor {int bLength; int /*<<< orphan*/  bCSourceID; int /*<<< orphan*/  bSourceID; int /*<<< orphan*/  iTerminal; int /*<<< orphan*/  wTerminalType; int /*<<< orphan*/  bTerminalID; } ;
struct uac1_output_terminal_descriptor {int bLength; int /*<<< orphan*/  bSourceID; int /*<<< orphan*/  iTerminal; int /*<<< orphan*/  wTerminalType; int /*<<< orphan*/  bTerminalID; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; void* type; int /*<<< orphan*/  id; } ;
struct mixer_build {TYPE_3__ oterm; int /*<<< orphan*/  unitbitmap; int /*<<< orphan*/  selector_map; int /*<<< orphan*/  map; TYPE_1__* chip; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buffer; struct usb_mixer_interface* mixer; } ;
typedef  int /*<<< orphan*/  state ;
struct TYPE_5__ {int /*<<< orphan*/  extralen; int /*<<< orphan*/  extra; } ;
struct TYPE_4__ {scalar_t__ usb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC_OUTPUT_TERMINAL ; 
 scalar_t__ UAC_VERSION_1 ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mixer_build*,int /*<<< orphan*/ ,int) ; 
 int parse_audio_unit (struct mixer_build*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* snd_usb_find_csint_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct usbmix_ctl_map* usbmix_ctl_maps ; 

__attribute__((used)) static int snd_usb_mixer_controls(struct usb_mixer_interface *mixer)
{
	struct mixer_build state;
	int err;
	const struct usbmix_ctl_map *map;
	void *p;

	memset(&state, 0, sizeof(state));
	state.chip = mixer->chip;
	state.mixer = mixer;
	state.buffer = mixer->hostif->extra;
	state.buflen = mixer->hostif->extralen;

	/* check the mapping table */
	for (map = usbmix_ctl_maps; map->id; map++) {
		if (map->id == state.chip->usb_id) {
			state.map = map->map;
			state.selector_map = map->selector_map;
			mixer->ignore_ctl_error = map->ignore_ctl_error;
			break;
		}
	}

	p = NULL;
	while ((p = snd_usb_find_csint_desc(mixer->hostif->extra, mixer->hostif->extralen,
					    p, UAC_OUTPUT_TERMINAL)) != NULL) {
		if (mixer->protocol == UAC_VERSION_1) {
			struct uac1_output_terminal_descriptor *desc = p;

			if (desc->bLength < sizeof(*desc))
				continue; /* invalid descriptor? */
			set_bit(desc->bTerminalID, state.unitbitmap);  /* mark terminal ID as visited */
			state.oterm.id = desc->bTerminalID;
			state.oterm.type = le16_to_cpu(desc->wTerminalType);
			state.oterm.name = desc->iTerminal;
			err = parse_audio_unit(&state, desc->bSourceID);
			if (err < 0)
				return err;
		} else { /* UAC_VERSION_2 */
			struct uac2_output_terminal_descriptor *desc = p;

			if (desc->bLength < sizeof(*desc))
				continue; /* invalid descriptor? */
			set_bit(desc->bTerminalID, state.unitbitmap);  /* mark terminal ID as visited */
			state.oterm.id = desc->bTerminalID;
			state.oterm.type = le16_to_cpu(desc->wTerminalType);
			state.oterm.name = desc->iTerminal;
			err = parse_audio_unit(&state, desc->bSourceID);
			if (err < 0)
				return err;

			/* for UAC2, use the same approach to also add the clock selectors */
			err = parse_audio_unit(&state, desc->bCSourceID);
			if (err < 0)
				return err;
		}
	}

	return 0;
}