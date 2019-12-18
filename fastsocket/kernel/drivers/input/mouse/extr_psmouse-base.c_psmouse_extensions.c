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
struct psmouse {int /*<<< orphan*/  ps2dev; } ;

/* Variables and functions */
 int PSMOUSE_ALPS ; 
 int /*<<< orphan*/  PSMOUSE_CMD_RESET_DIS ; 
 int PSMOUSE_ELANTECH ; 
 int PSMOUSE_FSP ; 
 int PSMOUSE_GENPS ; 
 int PSMOUSE_HGPK ; 
 unsigned int PSMOUSE_IMEX ; 
 unsigned int PSMOUSE_IMPS ; 
 int PSMOUSE_LIFEBOOK ; 
 unsigned int PSMOUSE_PS2 ; 
 int PSMOUSE_PS2PP ; 
 int PSMOUSE_SYNAPTICS ; 
 int PSMOUSE_THINKPS ; 
 int PSMOUSE_TOUCHKIT_PS2 ; 
 int PSMOUSE_TRACKPOINT ; 
 scalar_t__ alps_detect (struct psmouse*,int) ; 
 scalar_t__ alps_init (struct psmouse*) ; 
 scalar_t__ elantech_detect (struct psmouse*,int) ; 
 scalar_t__ elantech_init (struct psmouse*) ; 
 scalar_t__ fsp_detect (struct psmouse*,int) ; 
 scalar_t__ fsp_init (struct psmouse*) ; 
 scalar_t__ genius_detect (struct psmouse*,int) ; 
 scalar_t__ hgpk_detect (struct psmouse*,int) ; 
 scalar_t__ hgpk_init (struct psmouse*) ; 
 scalar_t__ im_explorer_detect (struct psmouse*,int) ; 
 scalar_t__ intellimouse_detect (struct psmouse*,int) ; 
 scalar_t__ lifebook_detect (struct psmouse*,int) ; 
 scalar_t__ lifebook_init (struct psmouse*) ; 
 int /*<<< orphan*/  ps2_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps2bare_detect (struct psmouse*,int) ; 
 scalar_t__ ps2pp_init (struct psmouse*,int) ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 
 scalar_t__ synaptics_detect (struct psmouse*,int) ; 
 scalar_t__ synaptics_init (struct psmouse*) ; 
 int /*<<< orphan*/  synaptics_reset (struct psmouse*) ; 
 scalar_t__ synaptics_supported () ; 
 scalar_t__ thinking_detect (struct psmouse*,int) ; 
 scalar_t__ touchkit_ps2_detect (struct psmouse*,int) ; 
 scalar_t__ trackpoint_detect (struct psmouse*,int) ; 

__attribute__((used)) static int psmouse_extensions(struct psmouse *psmouse,
			      unsigned int max_proto, bool set_properties)
{
	bool synaptics_hardware = false;

/*
 * We always check for lifebook because it does not disturb mouse
 * (it only checks DMI information).
 */
	if (lifebook_detect(psmouse, set_properties) == 0) {
		if (max_proto > PSMOUSE_IMEX) {
			if (!set_properties || lifebook_init(psmouse) == 0)
				return PSMOUSE_LIFEBOOK;
		}
	}

/*
 * Try Kensington ThinkingMouse (we try first, because synaptics probe
 * upsets the thinkingmouse).
 */

	if (max_proto > PSMOUSE_IMEX && thinking_detect(psmouse, set_properties) == 0)
		return PSMOUSE_THINKPS;

/*
 * Try Synaptics TouchPad. Note that probing is done even if Synaptics protocol
 * support is disabled in config - we need to know if it is synaptics so we
 * can reset it properly after probing for intellimouse.
 */
	if (max_proto > PSMOUSE_PS2 && synaptics_detect(psmouse, set_properties) == 0) {
		synaptics_hardware = true;

		if (max_proto > PSMOUSE_IMEX) {
/*
 * Try activating protocol, but check if support is enabled first, since
 * we try detecting Synaptics even when protocol is disabled.
 */
			if (synaptics_supported() &&
			    (!set_properties || synaptics_init(psmouse) == 0)) {
				return PSMOUSE_SYNAPTICS;
			}

/*
 * Some Synaptics touchpads can emulate extended protocols (like IMPS/2).
 * Unfortunately Logitech/Genius probes confuse some firmware versions so
 * we'll have to skip them.
 */
			max_proto = PSMOUSE_IMEX;
		}
/*
 * Make sure that touchpad is in relative mode, gestures (taps) are enabled
 */
		synaptics_reset(psmouse);
	}

/*
 * Try ALPS TouchPad
 */
	if (max_proto > PSMOUSE_IMEX) {
		ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_RESET_DIS);
		if (alps_detect(psmouse, set_properties) == 0) {
			if (!set_properties || alps_init(psmouse) == 0)
				return PSMOUSE_ALPS;
/*
 * Init failed, try basic relative protocols
 */
			max_proto = PSMOUSE_IMEX;
		}
	}

/*
 * Try OLPC HGPK touchpad.
 */
	if (max_proto > PSMOUSE_IMEX &&
			hgpk_detect(psmouse, set_properties) == 0) {
		if (!set_properties || hgpk_init(psmouse) == 0)
			return PSMOUSE_HGPK;
/*
 * Init failed, try basic relative protocols
 */
		max_proto = PSMOUSE_IMEX;
	}

/*
 * Try Elantech touchpad.
 */
	if (max_proto > PSMOUSE_IMEX &&
			elantech_detect(psmouse, set_properties) == 0) {
		if (!set_properties || elantech_init(psmouse) == 0)
			return PSMOUSE_ELANTECH;
/*
 * Init failed, try basic relative protocols
 */
		max_proto = PSMOUSE_IMEX;
	}


	if (max_proto > PSMOUSE_IMEX) {
		if (genius_detect(psmouse, set_properties) == 0)
			return PSMOUSE_GENPS;

		if (ps2pp_init(psmouse, set_properties) == 0)
			return PSMOUSE_PS2PP;

		if (trackpoint_detect(psmouse, set_properties) == 0)
			return PSMOUSE_TRACKPOINT;

		if (touchkit_ps2_detect(psmouse, set_properties) == 0)
			return PSMOUSE_TOUCHKIT_PS2;
	}

/*
 * Try Finger Sensing Pad. We do it here because its probe upsets
 * Trackpoint devices (causing TP_READ_ID command to time out).
 */
	if (max_proto > PSMOUSE_IMEX) {
		if (fsp_detect(psmouse, set_properties) == 0) {
			if (!set_properties || fsp_init(psmouse) == 0)
				return PSMOUSE_FSP;
/*
 * Init failed, try basic relative protocols
 */
			max_proto = PSMOUSE_IMEX;
		}
	}

/*
 * Reset to defaults in case the device got confused by extended
 * protocol probes. Note that we follow up with full reset because
 * some mice put themselves to sleep when they see PSMOUSE_RESET_DIS.
 */
	ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_RESET_DIS);
	psmouse_reset(psmouse);

	if (max_proto >= PSMOUSE_IMEX && im_explorer_detect(psmouse, set_properties) == 0)
		return PSMOUSE_IMEX;

	if (max_proto >= PSMOUSE_IMPS && intellimouse_detect(psmouse, set_properties) == 0)
		return PSMOUSE_IMPS;

/*
 * Okay, all failed, we have a standard mouse here. The number of the buttons
 * is still a question, though. We assume 3.
 */
	ps2bare_detect(psmouse, set_properties);

	if (synaptics_hardware) {
/*
 * We detected Synaptics hardware but it did not respond to IMPS/2 probes.
 * We need to reset the touchpad because if there is a track point on the
 * pass through port it could get disabled while probing for protocol
 * extensions.
 */
		psmouse_reset(psmouse);
	}

	return PSMOUSE_PS2;
}