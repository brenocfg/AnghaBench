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
struct tveeprom {int model; scalar_t__ tuner_type; scalar_t__ has_radio; int tuner_formats; } ;
struct TYPE_4__ {int tuner; int radio; } ;
struct cx18 {int std; TYPE_2__ options; int /*<<< orphan*/  card_name; TYPE_1__* card; int /*<<< orphan*/  card_i2c; int /*<<< orphan*/  v4l2_cap; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c; int /*<<< orphan*/  name; int /*<<< orphan*/  v4l2_capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_CARD_HVR_1600_ESMT ; 
 int /*<<< orphan*/  CX18_CARD_HVR_1600_S5H1411 ; 
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  CX18_ERR (char*,...) ; 
 int /*<<< orphan*/  CX18_INFO (char*,...) ; 
 scalar_t__ TUNER_ABSENT ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_NTSC_M ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_PAL_BG ; 
 int V4L2_STD_PAL_H ; 
 int V4L2_STD_SECAM ; 
 int V4L2_STD_SECAM_L ; 
 void* cx18_get_card (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_read_eeprom (struct cx18*,struct tveeprom*) ; 

__attribute__((used)) static void cx18_process_eeprom(struct cx18 *cx)
{
	struct tveeprom tv;

	cx18_read_eeprom(cx, &tv);

	/* Many thanks to Steven Toth from Hauppauge for providing the
	   model numbers */
	/* Note: the Samsung memory models cannot be reliably determined
	   from the model number. Use the cardtype module option if you
	   have one of these preproduction models. */
	switch (tv.model) {
	case 74301: /* Retail models */
	case 74321:
	case 74351: /* OEM models */
	case 74361:
		/* Digital side is s5h1411/tda18271 */
		cx->card = cx18_get_card(CX18_CARD_HVR_1600_S5H1411);
		break;
	case 74021: /* Retail models */
	case 74031:
	case 74041:
	case 74141:
	case 74541: /* OEM models */
	case 74551:
	case 74591:
	case 74651:
	case 74691:
	case 74751:
	case 74891:
		/* Digital side is s5h1409/mxl5005s */
		cx->card = cx18_get_card(CX18_CARD_HVR_1600_ESMT);
		break;
	case 0x718:
		return;
	case 0xffffffff:
		CX18_INFO("Unknown EEPROM encoding\n");
		return;
	case 0:
		CX18_ERR("Invalid EEPROM\n");
		return;
	default:
		CX18_ERR("Unknown model %d, defaulting to original HVR-1600 "
			 "(cardtype=1)\n", tv.model);
		cx->card = cx18_get_card(CX18_CARD_HVR_1600_ESMT);
		break;
	}

	cx->v4l2_cap = cx->card->v4l2_capabilities;
	cx->card_name = cx->card->name;
	cx->card_i2c = cx->card->i2c;

	CX18_INFO("Autodetected %s\n", cx->card_name);

	if (tv.tuner_type == TUNER_ABSENT)
		CX18_ERR("tveeprom cannot autodetect tuner!\n");

	if (cx->options.tuner == -1)
		cx->options.tuner = tv.tuner_type;
	if (cx->options.radio == -1)
		cx->options.radio = (tv.has_radio != 0);

	if (cx->std != 0)
		/* user specified tuner standard */
		return;

	/* autodetect tuner standard */
	if (tv.tuner_formats & V4L2_STD_PAL) {
		CX18_DEBUG_INFO("PAL tuner detected\n");
		cx->std |= V4L2_STD_PAL_BG | V4L2_STD_PAL_H;
	} else if (tv.tuner_formats & V4L2_STD_NTSC) {
		CX18_DEBUG_INFO("NTSC tuner detected\n");
		cx->std |= V4L2_STD_NTSC_M;
	} else if (tv.tuner_formats & V4L2_STD_SECAM) {
		CX18_DEBUG_INFO("SECAM tuner detected\n");
		cx->std |= V4L2_STD_SECAM_L;
	} else {
		CX18_INFO("No tuner detected, default to NTSC-M\n");
		cx->std |= V4L2_STD_NTSC_M;
	}
}