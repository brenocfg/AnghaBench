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
typedef  int /*<<< orphan*/  vga_modes ;
struct mode_info {int dummy; } ;
struct biosregs {int ax; int bl; int al; int /*<<< orphan*/  bx; } ;
typedef  int /*<<< orphan*/  ega_modes ;
typedef  int /*<<< orphan*/  cga_modes ;
struct TYPE_4__ {int orig_video_isVGA; int /*<<< orphan*/  orig_video_ega_bx; } ;
struct TYPE_6__ {TYPE_1__ screen_info; } ;
struct TYPE_5__ {char const* card_name; struct mode_info* modes; } ;

/* Variables and functions */
 size_t ADAPTER_CGA ; 
 size_t ADAPTER_EGA ; 
 size_t ADAPTER_VGA ; 
 size_t adapter ; 
 TYPE_3__ boot_params ; 
#define  cga_modes 130 
#define  ega_modes 129 
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,struct biosregs*) ; 
#define  vga_modes 128 
 TYPE_2__ video_vga ; 

__attribute__((used)) static int vga_probe(void)
{
	static const char *card_name[] = {
		"CGA/MDA/HGC", "EGA", "VGA"
	};
	static struct mode_info *mode_lists[] = {
		cga_modes,
		ega_modes,
		vga_modes,
	};
	static int mode_count[] = {
		sizeof(cga_modes)/sizeof(struct mode_info),
		sizeof(ega_modes)/sizeof(struct mode_info),
		sizeof(vga_modes)/sizeof(struct mode_info),
	};

	struct biosregs ireg, oreg;

	initregs(&ireg);

	ireg.ax = 0x1200;
	ireg.bl = 0x10;		/* Check EGA/VGA */
	intcall(0x10, &ireg, &oreg);

#ifndef _WAKEUP
	boot_params.screen_info.orig_video_ega_bx = oreg.bx;
#endif

	/* If we have MDA/CGA/HGC then BL will be unchanged at 0x10 */
	if (oreg.bl != 0x10) {
		/* EGA/VGA */
		ireg.ax = 0x1a00;
		intcall(0x10, &ireg, &oreg);

		if (oreg.al == 0x1a) {
			adapter = ADAPTER_VGA;
#ifndef _WAKEUP
			boot_params.screen_info.orig_video_isVGA = 1;
#endif
		} else {
			adapter = ADAPTER_EGA;
		}
	} else {
		adapter = ADAPTER_CGA;
	}

	video_vga.modes = mode_lists[adapter];
	video_vga.card_name = card_name[adapter];
	return mode_count[adapter];
}