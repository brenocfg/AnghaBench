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
 int PAHW_MCD ; 
 int PicoAHW ; 
 int extract_text (char*,scalar_t__,int,int) ; 
 scalar_t__ media_id_header ; 

void emu_get_game_name(char *str150)
{
	int ret, swab = (PicoAHW & PAHW_MCD) ? 0 : 1;
	char *s, *d;

	ret = extract_text(str150, media_id_header + 0x50, 0x30, swab); // overseas name

	for (s = d = str150 + 1; s < str150+ret; s++)
	{
		if (*s == 0) break;
		if (*s != ' ' || d[-1] != ' ')
			*d++ = *s;
	}
	*d = 0;
}