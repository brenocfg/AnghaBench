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
typedef  int u8 ;
struct vivi_fh {int input; } ;

/* Variables and functions */
 int BLACK ; 
 int TSTAMP_INPUT_X ; 
 int TSTAMP_MAX_Y ; 
 int TSTAMP_MIN_X ; 
 int TSTAMP_MIN_Y ; 
 int WHITE ; 
 int /*<<< orphan*/  gen_twopix (struct vivi_fh*,char*,int) ; 
 int* rom8x16_bits ; 
 int strlen (char*) ; 

__attribute__((used)) static void gen_line(struct vivi_fh *fh, char *basep, int inipos, int wmax,
		int hmax, int line, int count, char *timestr)
{
	int  w, i, j;
	int pos = inipos;
	char *s;
	u8 chr;

	/* We will just duplicate the second pixel at the packet */
	wmax /= 2;

	/* Generate a standard color bar pattern */
	for (w = 0; w < wmax; w++) {
		int colorpos = ((w + count) * 8/(wmax + 1)) % 8;

		gen_twopix(fh, basep + pos, colorpos);
		pos += 4; /* only 16 bpp supported for now */
	}

	/* Prints input entry number */

	/* Checks if it is possible to input number */
	if (TSTAMP_MAX_Y >= hmax)
		goto end;

	if (TSTAMP_INPUT_X + strlen(timestr) >= wmax)
		goto end;

	if (line >= TSTAMP_MIN_Y && line <= TSTAMP_MAX_Y) {
		chr = rom8x16_bits[fh->input * 16 + line - TSTAMP_MIN_Y];
		pos = TSTAMP_INPUT_X;
		for (i = 0; i < 7; i++) {
			/* Draw white font on black background */
			if (chr & 1 << (7 - i))
				gen_twopix(fh, basep + pos, WHITE);
			else
				gen_twopix(fh, basep + pos, BLACK);
			pos += 2;
		}
	}

	/* Checks if it is possible to show timestamp */
	if (TSTAMP_MIN_X + strlen(timestr) >= wmax)
		goto end;

	/* Print stream time */
	if (line >= TSTAMP_MIN_Y && line <= TSTAMP_MAX_Y) {
		j = TSTAMP_MIN_X;
		for (s = timestr; *s; s++) {
			chr = rom8x16_bits[(*s-0x30)*16+line-TSTAMP_MIN_Y];
			for (i = 0; i < 7; i++) {
				pos = inipos + j * 2;
				/* Draw white font on black background */
				if (chr & 1 << (7 - i))
					gen_twopix(fh, basep + pos, WHITE);
				else
					gen_twopix(fh, basep + pos, BLACK);
				j++;
			}
		}
	}

end:
	return;
}