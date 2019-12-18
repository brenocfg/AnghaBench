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

__attribute__((used)) static const char *tifm_media_type_name(unsigned char type, unsigned char nt)
{
	const char *card_type_name[3][3] = {
		{ "SmartMedia/xD", "MemoryStick", "MMC/SD" },
		{ "XD", "MS", "SD"},
		{ "xd", "ms", "sd"}
	};

	if (nt > 2 || type < 1 || type > 3)
		return NULL;
	return card_type_name[nt][type - 1];
}