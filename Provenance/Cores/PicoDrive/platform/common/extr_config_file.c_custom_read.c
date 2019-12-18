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
struct TYPE_5__ {int Frameskip; int msh2_khz; int ssh2_khz; int EmuOpt; void* hscale40; void* hscale32; void* scale; void* gamma; } ;

/* Variables and functions */
#define  MA_32XOPT_MSH2_CYCLES 137 
#define  MA_32XOPT_SSH2_CYCLES 136 
#define  MA_OPT2_GAMMA 135 
#define  MA_OPT3_HSCALE32 134 
#define  MA_OPT3_HSCALE40 133 
#define  MA_OPT3_SCALE 132 
#define  MA_OPT3_VSYNC 131 
#define  MA_OPT_FRAMESKIP 130 
#define  MA_OPT_REGION 129 
#define  MA_OPT_SOUND_QUALITY 128 
 int /*<<< orphan*/  POPT_EN_STEREO ; 
 int /*<<< orphan*/  Pico32xSetClocks (int,int) ; 
 int PicoAutoRgnOrder ; 
 int /*<<< orphan*/  PicoOpt ; 
 int PicoRegionOverride ; 
 int PsndRate ; 
 void* atof (char const*) ; 
 void* atoi (char const*) ; 
 TYPE_3__ currentConfig ; 
 int /*<<< orphan*/  lprintf (char*,int,char const*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 
 int strtoul (char const*,char**,int) ; 

__attribute__((used)) static int custom_read(menu_entry *me, const char *var, const char *val)
{
	char *tmp;

	switch (me->id)
	{
		case MA_OPT_FRAMESKIP:
			if (strcasecmp(var, "Frameskip") != 0) return 0;
			if (strcasecmp(val, "Auto") == 0)
			     currentConfig.Frameskip = -1;
			else currentConfig.Frameskip = atoi(val);
			return 1;

		case MA_OPT_SOUND_QUALITY:
			if (strcasecmp(var, "Sound Quality") != 0) return 0;
			PsndRate = strtoul(val, &tmp, 10);
			if (PsndRate < 8000 || PsndRate > 44100)
				PsndRate = 22050;
			if (*tmp == 'H' || *tmp == 'h') tmp++;
			if (*tmp == 'Z' || *tmp == 'z') tmp++;
			while (*tmp == ' ') tmp++;
			if        (strcasecmp(tmp, "stereo") == 0) {
				PicoOpt |=  POPT_EN_STEREO;
			} else if (strcasecmp(tmp, "mono") == 0) {
				PicoOpt &= ~POPT_EN_STEREO;
			} else
				return 0;
			return 1;

		case MA_OPT_REGION:
			if (strcasecmp(var, "Region") != 0) return 0;
			if       (strncasecmp(val, "Auto: ", 6) == 0)
			{
				const char *p = val + 5, *end = val + strlen(val);
				int i;
				PicoRegionOverride = PicoAutoRgnOrder = 0;
				for (i = 0; p < end && i < 3; i++)
				{
					while (*p == ' ') p++;
					if        (p[0] == 'J' && p[1] == 'P') {
						PicoAutoRgnOrder |= 1 << (i*4);
					} else if (p[0] == 'U' && p[1] == 'S') {
						PicoAutoRgnOrder |= 4 << (i*4);
					} else if (p[0] == 'E' && p[1] == 'U') {
						PicoAutoRgnOrder |= 8 << (i*4);
					}
					while (*p != ' ' && *p != 0) p++;
					if (*p == 0) break;
				}
			}
			else   if (strcasecmp(val, "Auto") == 0) {
				PicoRegionOverride = 0;
			} else if (strcasecmp(val, "Japan NTSC") == 0) {
				PicoRegionOverride = 1;
			} else if (strcasecmp(val, "Japan PAL") == 0) {
				PicoRegionOverride = 2;
			} else if (strcasecmp(val, "USA") == 0) {
				PicoRegionOverride = 4;
			} else if (strcasecmp(val, "Europe") == 0) {
				PicoRegionOverride = 8;
			} else
				return 0;
			return 1;

		case MA_32XOPT_MSH2_CYCLES:
			currentConfig.msh2_khz = atoi(val);
			Pico32xSetClocks(currentConfig.msh2_khz * 1000, 0);
			return 1;

		case MA_32XOPT_SSH2_CYCLES:
			currentConfig.ssh2_khz = atoi(val);
			Pico32xSetClocks(0, currentConfig.ssh2_khz * 1000);
			return 1;

		case MA_OPT2_GAMMA:
			currentConfig.gamma = atoi(val);
			return 1;

		/* PSP */
		case MA_OPT3_SCALE:
			if (strcasecmp(var, "Scale factor") != 0) return 0;
			currentConfig.scale = atof(val);
			return 1;
		case MA_OPT3_HSCALE32:
			if (strcasecmp(var, "Hor. scale (for low res. games)") != 0) return 0;
			currentConfig.hscale32 = atof(val);
			return 1;
		case MA_OPT3_HSCALE40:
			if (strcasecmp(var, "Hor. scale (for hi res. games)") != 0) return 0;
			currentConfig.hscale40 = atof(val);
			return 1;
		case MA_OPT3_VSYNC:
			// XXX: use enum
			if (strcasecmp(var, "Wait for vsync") != 0) return 0;
			if        (strcasecmp(val, "never") == 0) {
				currentConfig.EmuOpt &= ~0x12000;
			} else if (strcasecmp(val, "sometimes") == 0) {
				currentConfig.EmuOpt |=  0x12000;
			} else if (strcasecmp(val, "always") == 0) {
				currentConfig.EmuOpt &= ~0x12000;
				currentConfig.EmuOpt |=  0x02000;
			} else
				return 0;
			return 1;

		default:
			lprintf("unhandled custom_read %i: %s\n", me->id, var);
			return 0;
	}
}