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
typedef  int /*<<< orphan*/  u8 ;
struct tveeprom {int model; scalar_t__ has_radio; int /*<<< orphan*/  tuner_formats; int /*<<< orphan*/  tuner_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ radio; int /*<<< orphan*/  tuner_type; } ;
struct cx88_core {TYPE_2__ board; int /*<<< orphan*/  tuner_formats; int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
#define  CX88_BOARD_SAMSUNG_SMT_7020 128 
 int /*<<< orphan*/  CX88_RADIO ; 
 int /*<<< orphan*/  MO_GP0_IO ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  info_printk (struct cx88_core*,char*,int) ; 
 int /*<<< orphan*/  tveeprom_hauppauge_analog (int /*<<< orphan*/ *,struct tveeprom*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn_printk (struct cx88_core*,char*,int) ; 

__attribute__((used)) static void hauppauge_eeprom(struct cx88_core *core, u8 *eeprom_data)
{
	struct tveeprom tv;

	tveeprom_hauppauge_analog(&core->i2c_client, &tv, eeprom_data);
	core->board.tuner_type = tv.tuner_type;
	core->tuner_formats = tv.tuner_formats;
	core->board.radio.type = tv.has_radio ? CX88_RADIO : 0;

	/* Make sure we support the board model */
	switch (tv.model)
	{
	case 14009: /* WinTV-HVR3000 (Retail, IR, b/panel video, 3.5mm audio in) */
	case 14019: /* WinTV-HVR3000 (Retail, IR Blaster, b/panel video, 3.5mm audio in) */
	case 14029: /* WinTV-HVR3000 (Retail, IR, b/panel video, 3.5mm audio in - 880 bridge) */
	case 14109: /* WinTV-HVR3000 (Retail, IR, b/panel video, 3.5mm audio in - low profile) */
	case 14129: /* WinTV-HVR3000 (Retail, IR, b/panel video, 3.5mm audio in - 880 bridge - LP) */
	case 14559: /* WinTV-HVR3000 (OEM, no IR, b/panel video, 3.5mm audio in) */
	case 14569: /* WinTV-HVR3000 (OEM, no IR, no back panel video) */
	case 14659: /* WinTV-HVR3000 (OEM, no IR, b/panel video, RCA audio in - Low profile) */
	case 14669: /* WinTV-HVR3000 (OEM, no IR, no b/panel video - Low profile) */
	case 28552: /* WinTV-PVR 'Roslyn' (No IR) */
	case 34519: /* WinTV-PCI-FM */
	case 69009:
		/* WinTV-HVR4000 (DVBS/S2/T, Video and IR, back panel inputs) */
	case 69100: /* WinTV-HVR4000LITE (DVBS/S2, IR) */
	case 69500: /* WinTV-HVR4000LITE (DVBS/S2, No IR) */
	case 69559:
		/* WinTV-HVR4000 (DVBS/S2/T, Video no IR, back panel inputs) */
	case 69569: /* WinTV-HVR4000 (DVBS/S2/T, Video no IR) */
	case 90002: /* Nova-T-PCI (9002) */
	case 92001: /* Nova-S-Plus (Video and IR) */
	case 92002: /* Nova-S-Plus (Video and IR) */
	case 90003: /* Nova-T-PCI (9002 No RF out) */
	case 90500: /* Nova-T-PCI (oem) */
	case 90501: /* Nova-T-PCI (oem/IR) */
	case 92000: /* Nova-SE2 (OEM, No Video or IR) */
	case 92900: /* WinTV-IROnly (No analog or digital Video inputs) */
	case 94009: /* WinTV-HVR1100 (Video and IR Retail) */
	case 94501: /* WinTV-HVR1100 (Video and IR OEM) */
	case 96009: /* WinTV-HVR1300 (PAL Video, MPEG Video and IR RX) */
	case 96019: /* WinTV-HVR1300 (PAL Video, MPEG Video and IR RX/TX) */
	case 96559: /* WinTV-HVR1300 (PAL Video, MPEG Video no IR) */
	case 96569: /* WinTV-HVR1300 () */
	case 96659: /* WinTV-HVR1300 () */
	case 98559: /* WinTV-HVR1100LP (Video no IR, Retail - Low Profile) */
		/* known */
		break;
	case CX88_BOARD_SAMSUNG_SMT_7020:
		cx_set(MO_GP0_IO, 0x008989FF);
		break;
	default:
		warn_printk(core, "warning: unknown hauppauge model #%d\n",
			    tv.model);
		break;
	}

	info_printk(core, "hauppauge eeprom: model=%d\n", tv.model);
}