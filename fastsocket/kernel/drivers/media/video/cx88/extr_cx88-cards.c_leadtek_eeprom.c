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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_type; } ;
struct cx88_core {TYPE_1__ board; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNER_PHILIPS_FM1216ME_MK3 ; 
 int /*<<< orphan*/  TUNER_PHILIPS_FM1236_MK3 ; 
 int /*<<< orphan*/  info_printk (struct cx88_core*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warn_printk (struct cx88_core*,char*) ; 

__attribute__((used)) static void leadtek_eeprom(struct cx88_core *core, u8 *eeprom_data)
{
	if (eeprom_data[4] != 0x7d ||
	    eeprom_data[5] != 0x10 ||
	    eeprom_data[7] != 0x66) {
		warn_printk(core, "Leadtek eeprom invalid.\n");
		return;
	}

	/* Terry Wu <terrywu2009@gmail.com> */
	switch (eeprom_data[6]) {
	case 0x13: /* SSID 6613 for TV2000 XP Expert NTSC Model */
	case 0x21: /* SSID 6621 for DV2000 NTSC Model */
	case 0x31: /* SSID 6631 for PVR2000 NTSC Model */
	case 0x37: /* SSID 6637 for PVR2000 NTSC Model */
	case 0x3d: /* SSID 6637 for PVR2000 NTSC Model */
		core->board.tuner_type = TUNER_PHILIPS_FM1236_MK3;
		break;
	default:
		core->board.tuner_type = TUNER_PHILIPS_FM1216ME_MK3;
		break;
	}

	info_printk(core, "Leadtek Winfast 2000XP Expert config: "
		    "tuner=%d, eeprom[0]=0x%02x\n",
		    core->board.tuner_type, eeprom_data[0]);
}