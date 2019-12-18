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
typedef  size_t UBYTE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ATARI_VISIBLE_WIDTH ; 
 int Colours_GetB (int) ; 
 int Colours_GetG (int) ; 
 int Colours_GetR (int) ; 
 size_t* Colours_table ; 
 int Screen_HEIGHT ; 
 int Screen_WIDTH ; 
 int /*<<< orphan*/  fputc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputw (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Screen_SavePCX(FILE *fp, UBYTE *ptr1, UBYTE *ptr2)
{
	int i;
	int x;
	int y;
	UBYTE plane = 16;	/* 16 = Red, 8 = Green, 0 = Blue */
	UBYTE last;
	UBYTE count;

	fputc(0xa, fp);   /* pcx signature */
	fputc(0x5, fp);   /* version 5 */
	fputc(0x1, fp);   /* RLE encoding */
	fputc(0x8, fp);   /* bits per pixel */
	fputw(0, fp);     /* XMin */
	fputw(0, fp);     /* YMin */
	fputw(ATARI_VISIBLE_WIDTH - 1, fp); /* XMax */
	fputw(Screen_HEIGHT - 1, fp);        /* YMax */
	fputw(0, fp);     /* HRes */
	fputw(0, fp);     /* VRes */
	for (i = 0; i < 48; i++)
		fputc(0, fp); /* EGA color palette */
	fputc(0, fp);     /* reserved */
	fputc(ptr2 != NULL ? 3 : 1, fp); /* number of bit planes */
	fputw(ATARI_VISIBLE_WIDTH, fp);  /* number of bytes per scan line per color plane */
	fputw(1, fp);     /* palette info */
	fputw(ATARI_VISIBLE_WIDTH, fp); /* screen resolution */
	fputw(Screen_HEIGHT, fp);
	for (i = 0; i < 54; i++)
		fputc(0, fp);  /* unused */

	for (y = 0; y < Screen_HEIGHT; ) {
		x = 0;
		do {
			last = ptr2 != NULL ? (((Colours_table[*ptr1] >> plane) & 0xff) + ((Colours_table[*ptr2] >> plane) & 0xff)) >> 1 : *ptr1;
			count = 0xc0;
			do {
				ptr1++;
				if (ptr2 != NULL)
					ptr2++;
				count++;
				x++;
			} while (last == (ptr2 != NULL ? (((Colours_table[*ptr1] >> plane) & 0xff) + ((Colours_table[*ptr2] >> plane) & 0xff)) >> 1 : *ptr1)
						&& count < 0xff && x < ATARI_VISIBLE_WIDTH);
			if (count > 0xc1 || last >= 0xc0)
				fputc(count, fp);
			fputc(last, fp);
		} while (x < ATARI_VISIBLE_WIDTH);

		if (ptr2 != NULL && plane) {
			ptr1 -= ATARI_VISIBLE_WIDTH;
			ptr2 -= ATARI_VISIBLE_WIDTH;
			plane -= 8;
		}
		else {
			ptr1 += Screen_WIDTH - ATARI_VISIBLE_WIDTH;
			if (ptr2 != NULL) {
				ptr2 += Screen_WIDTH - ATARI_VISIBLE_WIDTH;
				plane = 16;
			}
			y++;
		}
	}

	if (ptr2 == NULL) {
		/* write palette */
		fputc(0xc, fp);
		for (i = 0; i < 256; i++) {
			fputc(Colours_GetR(i), fp);
			fputc(Colours_GetG(i), fp);
			fputc(Colours_GetB(i), fp);
		}
	}
}