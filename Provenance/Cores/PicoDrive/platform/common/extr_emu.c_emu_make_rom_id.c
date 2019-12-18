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
typedef  int /*<<< orphan*/  id_string ;

/* Variables and functions */
 int PAHW_MCD ; 
 int PAHW_SMS ; 
 int PicoAHW ; 
 scalar_t__ extract_text (char*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  fname_ext (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ media_id_header ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *emu_make_rom_id(const char *fname)
{
	static char id_string[3+0xe*3+0x3*3+0x30*3+3];
	int pos, swab = 1;

	if (PicoAHW & PAHW_MCD) {
		strcpy(id_string, "CD|");
		swab = 0;
	}
	else if (PicoAHW & PAHW_SMS)
		strcpy(id_string, "MS|");
	else	strcpy(id_string, "MD|");
	pos = 3;

	if (!(PicoAHW & PAHW_SMS)) {
		pos += extract_text(id_string + pos, media_id_header + 0x80, 0x0e, swab); // serial
		id_string[pos] = '|'; pos++;
		pos += extract_text(id_string + pos, media_id_header + 0xf0, 0x03, swab); // region
		id_string[pos] = '|'; pos++;
		pos += extract_text(id_string + pos, media_id_header + 0x50, 0x30, swab); // overseas name
		id_string[pos] = 0;
		if (pos > 5)
			return id_string;
		pos = 3;
	}

	// can't find name in ROM, use filename
	fname_ext(id_string + 3, sizeof(id_string) - 3, NULL, NULL, fname);

	return id_string;
}