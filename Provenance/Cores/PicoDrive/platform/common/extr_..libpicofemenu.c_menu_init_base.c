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
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LC_TIME ; 
 scalar_t__ MENU_X2 ; 
 int /*<<< orphan*/  READPNG_FONT ; 
 int /*<<< orphan*/  READPNG_SELECTOR ; 
 unsigned char* calloc (int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 unsigned char* fontdata8x8 ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  lprintf (char*,...) ; 
 int me_mfont_h ; 
 int me_mfont_w ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 unsigned char* menu_font_data ; 
 int menu_sel_color ; 
 int menu_text_color ; 
 int parse_hex_color (char*) ; 
 int plat_get_skin_dir (char*,int) ; 
 int /*<<< orphan*/  readpng (unsigned char*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void menu_init_base(void)
{
	int i, c, l, pos;
	unsigned char *fd, *fds;
	char buff[256];
	FILE *f;

	if (menu_font_data != NULL)
		free(menu_font_data);

	menu_font_data = calloc((MENU_X2 ? 256 * 320 : 128 * 160) / 2, 1);
	if (menu_font_data == NULL)
		return;

	// generate default 8x10 font from fontdata8x8
	for (c = 0, fd = menu_font_data; c < 256; c++)
	{
		for (l = 0; l < 8; l++)
		{
			unsigned char fd8x8 = fontdata8x8[c*8+l];
			if (fd8x8&0x80) *fd  = 0xf0;
			if (fd8x8&0x40) *fd |= 0x0f; fd++;
			if (fd8x8&0x20) *fd  = 0xf0;
			if (fd8x8&0x10) *fd |= 0x0f; fd++;
			if (fd8x8&0x08) *fd  = 0xf0;
			if (fd8x8&0x04) *fd |= 0x0f; fd++;
			if (fd8x8&0x02) *fd  = 0xf0;
			if (fd8x8&0x01) *fd |= 0x0f; fd++;
		}
		fd += 8*2/2; // 2 empty lines
	}

	if (MENU_X2) {
		// expand default font
		fds = menu_font_data + 128 * 160 / 2 - 4;
		fd  = menu_font_data + 256 * 320 / 2 - 1;
		for (c = 255; c >= 0; c--)
		{
			for (l = 9; l >= 0; l--, fds -= 4)
			{
				for (i = 3; i >= 0; i--) {
					int px = fds[i] & 0x0f;
					*fd-- = px | (px << 4);
					px = (fds[i] >> 4) & 0x0f;
					*fd-- = px | (px << 4);
				}
				for (i = 3; i >= 0; i--) {
					int px = fds[i] & 0x0f;
					*fd-- = px | (px << 4);
					px = (fds[i] >> 4) & 0x0f;
					*fd-- = px | (px << 4);
				}
			}
		}
	}

	// load custom font and selector (stored as 1st symbol in font table)
	pos = plat_get_skin_dir(buff, sizeof(buff));
	strcpy(buff + pos, "font.png");
	readpng(menu_font_data, buff, READPNG_FONT,
		MENU_X2 ? 256 : 128, MENU_X2 ? 320 : 160);
	// default selector symbol is '>'
	memcpy(menu_font_data, menu_font_data + ((int)'>') * me_mfont_w * me_mfont_h / 2,
		me_mfont_w * me_mfont_h / 2);
	strcpy(buff + pos, "selector.png");
	readpng(menu_font_data, buff, READPNG_SELECTOR, me_mfont_w, me_mfont_h);

	// load custom colors
	strcpy(buff + pos, "skin.txt");
	f = fopen(buff, "r");
	if (f != NULL)
	{
		lprintf("found skin.txt\n");
		while (!feof(f))
		{
			if (fgets(buff, sizeof(buff), f) == NULL)
				break;
			if (buff[0] == '#'  || buff[0] == '/')  continue; // comment
			if (buff[0] == '\r' || buff[0] == '\n') continue; // empty line
			if (strncmp(buff, "text_color=", 11) == 0)
			{
				int tmp = parse_hex_color(buff+11);
				if (tmp >= 0) menu_text_color = tmp;
				else lprintf("skin.txt: parse error for text_color\n");
			}
			else if (strncmp(buff, "selection_color=", 16) == 0)
			{
				int tmp = parse_hex_color(buff+16);
				if (tmp >= 0) menu_sel_color = tmp;
				else lprintf("skin.txt: parse error for selection_color\n");
			}
			else
				lprintf("skin.txt: parse error: %s\n", buff);
		}
		fclose(f);
	}

	// use user's locale for savestate date display
	setlocale(LC_TIME, "");
}