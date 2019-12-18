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

/* Variables and functions */
 int PicoAutoRgnOrder ; 
 int PicoRegionOverride ; 
 char const* static_buff ; 
 int /*<<< orphan*/  strcat (char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char const*,char*) ; 

__attribute__((used)) static const char *mgn_opt_region(int id, int *offs)
{
	static const char *names[] = { "Auto", "      Japan NTSC", "      Japan PAL", "      USA", "      Europe" };
	static const char *names_short[] = { "", " JP", " JP", " US", " EU" };
	int code = PicoRegionOverride;
	int u, i = 0;

	*offs = -6;
	if (code) {
		code <<= 1;
		while ((code >>= 1)) i++;
		if (i > 4)
			return "unknown";
		return names[i];
	} else {
		strcpy(static_buff, "Auto:");
		for (u = 0; u < 3; u++) {
			code = (PicoAutoRgnOrder >> u*4) & 0xf;
			for (i = 0; code; code >>= 1, i++)
				;
			strcat(static_buff, names_short[i]);
		}
		return static_buff;
	}
}