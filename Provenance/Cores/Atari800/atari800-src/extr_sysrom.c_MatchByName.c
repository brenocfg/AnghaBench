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
struct TYPE_2__ {scalar_t__ unset; } ;

/* Variables and functions */
#define  SYSROM_5200_CUSTOM 131 
#define  SYSROM_800_CUSTOM 130 
#define  SYSROM_BASIC_CUSTOM 129 
#define  SYSROM_XL_CUSTOM 128 
 TYPE_1__* SYSROM_roms ; 
 scalar_t__ strcmp (char const*,char const* const) ; 

__attribute__((used)) static int MatchByName(char const *filename, int len, int only_if_not_set)
{
	static char const * const common_filenames[] = {
		"atariosa.rom", "atari_osa.rom", "atari_os_a.rom",
		"atariosb.rom", "atari_osb.rom", "atari_os_b.rom",
		NULL,
		"atarixlxe.rom", "atarixl.rom", "atari_xlxe.rom", "atari_xl_xe.rom",
		NULL,
		"atari5200.rom", "atar5200.rom", "5200.rom", "5200.bin", "atari_5200.rom",
		NULL,
		"ataribasic.rom", "ataribas.rom", "basic.rom", "atari_basic.rom",
		NULL
	};
	static struct { int const len; int const id; int const offset; } const offsets[] = {
			{ 0x2800, SYSROM_800_CUSTOM, 0 },
			{ 0x4000, SYSROM_XL_CUSTOM, 7 },
			{ 0x800, SYSROM_5200_CUSTOM, 12 },
			{ 0x2000, SYSROM_BASIC_CUSTOM, 18 }
	};
	int i;

	for (i = 0; i < 4; ++i) {
		if (len == offsets[i].len
		    && (!only_if_not_set || SYSROM_roms[i].unset)) {
			/* Start at common filename indexed by OFFSET, end if NULL reached. */
			char const * const *common_filename = common_filenames + offsets[i].offset;
			do {
				if (strcmp(filename, *common_filename) == 0)
					return offsets[i].id;
			} while (*++common_filename != NULL);
		}
	}
	return -1;
}