#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int id; } ;
typedef  TYPE_1__ menu_entry ;
struct TYPE_5__ {char* scale; char* hscale32; char* hscale40; char* gamma; char* gamma2; int EmuOpt; int /*<<< orphan*/  scaling; } ;

/* Variables and functions */
#define  MA_OPT3_BLACKLVL 134 
#define  MA_OPT3_FILTERING 133 
#define  MA_OPT3_GAMMAA 132 
#define  MA_OPT3_HSCALE32 131 
#define  MA_OPT3_HSCALE40 130 
#define  MA_OPT3_SCALE 129 
#define  MA_OPT3_VSYNC 128 
 TYPE_3__ currentConfig ; 
 int /*<<< orphan*/  text_out16 (int,int,char*,char*) ; 

__attribute__((used)) static void menu_opt3_cust_draw(const menu_entry *entry, int x, int y, void *param)
{
	switch (entry->id)
	{
		case MA_OPT3_SCALE:
			text_out16(x, y, "Scale factor:                      %.2f", currentConfig.scale);
			break;
		case MA_OPT3_HSCALE32:
			text_out16(x, y, "Hor. scale (for low res. games):   %.2f", currentConfig.hscale32);
			break;
		case MA_OPT3_HSCALE40:
			text_out16(x, y, "Hor. scale (for hi res. games):    %.2f", currentConfig.hscale40);
			break;
		case MA_OPT3_FILTERING:
			text_out16(x, y, "Bilinear filtering                 %s", currentConfig.scaling?"ON":"OFF");
			break;
		case MA_OPT3_GAMMAA:
			text_out16(x, y, "Gamma adjustment                  %2i", currentConfig.gamma);
			break;
		case MA_OPT3_BLACKLVL:
			text_out16(x, y, "Black level                       %2i", currentConfig.gamma2);
			break;
		case MA_OPT3_VSYNC: {
			char *val = "    never";
			if (currentConfig.EmuOpt & 0x2000)
				val = (currentConfig.EmuOpt & 0x10000) ? "sometimes" : "   always";
			text_out16(x, y, "Wait for vsync (slow)         %s", val);
			break;
		}
		default: break;
	}
}