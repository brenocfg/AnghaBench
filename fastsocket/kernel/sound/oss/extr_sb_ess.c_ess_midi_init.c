#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct address_info {int io_base; int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int submodel; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int abs (int /*<<< orphan*/ ) ; 
 int ess_getmixer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ess_setmixer (TYPE_1__*,int,unsigned char) ; 

int ess_midi_init(sb_devc * devc, struct address_info *hw_config)
{
	unsigned char   cfg, tmp;

	cfg = ess_getmixer (devc, 0x40) & 0x03;

	if (devc->submodel < 8) {
		ess_setmixer (devc, 0x40, cfg | 0x03);	/* Enable OPL3 & joystick */
		return 0;  					 /* ES688 doesn't support MPU401 mode */
	}
	tmp = (hw_config->io_base & 0x0f0) >> 4;

	if (tmp > 3) {
		ess_setmixer (devc, 0x40, cfg);
		return 0;
	}
	cfg |= tmp << 3;

	tmp = 1;		/* MPU enabled without interrupts */

	/* May be shared: if so the value is -ve */

	switch (abs(hw_config->irq)) {
		case 9:
			tmp = 0x4;
			break;
		case 5:
			tmp = 0x5;
			break;
		case 7:
			tmp = 0x6;
			break;
		case 10:
			tmp = 0x7;
			break;
		default:
			return 0;
	}

	cfg |= tmp << 5;
	ess_setmixer (devc, 0x40, cfg | 0x03);

	return 1;
}