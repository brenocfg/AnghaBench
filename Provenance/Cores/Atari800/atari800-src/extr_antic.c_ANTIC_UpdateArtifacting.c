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
typedef  void* UWORD ;
typedef  int UBYTE ;

/* Variables and functions */
 int ANTIC_artif_mode ; 
 scalar_t__ ANTIC_artif_new ; 
 int* ANTIC_cl ; 
 int ART_BLUE ; 
 int ART_BRIGHT_BROWN ; 
 int ART_BROWN ; 
 int ART_DARK_BLUE ; 
 int ART_GREEN ; 
 int ART_RED ; 
 size_t C_PF1 ; 
 size_t C_PF2 ; 
 int GTIA_COLPF2 ; 
 scalar_t__* art_bkmask_normal ; 
 scalar_t__* art_bkmask_reverse ; 
 void* art_colour1_new ; 
 void* art_colour2_new ; 
 scalar_t__ art_lookup_normal ; 
 scalar_t__ art_lookup_reverse ; 
 scalar_t__* art_lummask_normal ; 
 scalar_t__* art_lummask_reverse ; 
 int art_normal_colpf1_save ; 
 int art_normal_colpf2_save ; 
 int art_reverse_colpf1_save ; 
 int art_reverse_colpf2_save ; 
 int /*<<< orphan*/  draw_antic_2 ; 
 int /*<<< orphan*/  draw_antic_2_artif ; 
 int /*<<< orphan*/  draw_antic_2_artif_new ; 
 int /*<<< orphan*/  draw_antic_f ; 
 int /*<<< orphan*/  draw_antic_f_artif ; 
 int /*<<< orphan*/  draw_antic_f_artif_new ; 
 int /*<<< orphan*/ ** draw_antic_table ; 

void ANTIC_UpdateArtifacting(void)
{
#define ART_BROWN 0
#define ART_BLUE 1
#define ART_DARK_BROWN 2
#define ART_DARK_BLUE 3
#define ART_BRIGHT_BROWN 4
#define ART_BRIGHT_BLUE 5
#define ART_RED 6
#define ART_GREEN 7
	static const UBYTE art_colour_table[4][8] = {
		{ 0x88, 0x14, 0x88, 0x14, 0x8f, 0x1f, 0xbb, 0x5f },	/* brownblue */
		{ 0x14, 0x88, 0x14, 0x88, 0x1f, 0x8f, 0x5f, 0xbb },	/* bluebrown */
		{ 0xd6, 0x46, 0xd6, 0x46, 0xdf, 0x4a, 0x4f, 0xac },	/* redgreen */
		{ 0x46, 0xd6, 0x46, 0xd6, 0x4a, 0xdf, 0xac, 0x4f }	/* greenred */
	};

	int i;
	int j;
	int c;
	const UBYTE *art_colours;
	UBYTE q;
	UBYTE art_white;

	if (ANTIC_artif_mode == 0) {
		draw_antic_table[0][2] = draw_antic_table[0][3] = draw_antic_2;
		draw_antic_table[0][0xf] = draw_antic_f;
		return;
	}

#ifndef USE_COLOUR_TRANSLATION_TABLE
	if (ANTIC_artif_new) {
		static UWORD new_art_colour_table[4][2] = {
			{0x4040, 0x8080},
			{0x8080, 0x4040},
			{0x8080, 0xd0d0},
			{0xd0d0, 0x8080}
		};
		draw_antic_table[0][2] = draw_antic_table[0][3] = draw_antic_2_artif_new;
		draw_antic_table[0][0xf] = draw_antic_f_artif_new;
		art_colour1_new = new_art_colour_table[ANTIC_artif_mode - 1][0];
		art_colour2_new = new_art_colour_table[ANTIC_artif_mode - 1][1];
	}
	else
#endif
	{
		draw_antic_table[0][2] = draw_antic_table[0][3] = draw_antic_2_artif;
		draw_antic_table[0][0xf] = draw_antic_f_artif;
	}

	art_colours = (ANTIC_artif_mode <= 4 ? art_colour_table[ANTIC_artif_mode - 1] : art_colour_table[2]);

	art_reverse_colpf1_save = art_normal_colpf1_save = ANTIC_cl[C_PF1] & 0x0f0f;
	art_reverse_colpf2_save = art_normal_colpf2_save = ANTIC_cl[C_PF2];
	art_white = (ANTIC_cl[C_PF2] & 0xf0) | (ANTIC_cl[C_PF1] & 0x0f);

	for (i = 0; i <= 255; i++) {
		art_bkmask_normal[i] = 0;
		art_lummask_normal[i] = 0;
		art_bkmask_reverse[255 - i] = 0;
		art_lummask_reverse[255 - i] = 0;

		for (j = 0; j <= 3; j++) {
			q = i << j;
			if (!(q & 0x20)) {
				if ((q & 0xf8) == 0x50)
					c = ART_BLUE;				/* 01010 */
				else if ((q & 0xf8) == 0xD8)
					c = ART_DARK_BLUE;			/* 11011 */
				else {							/* xx0xx */
					((UBYTE *) art_lookup_normal)[(i << 2) + j] = GTIA_COLPF2;
					((UBYTE *) art_lookup_reverse)[((255 - i) << 2) + j] = art_white;
					((UBYTE *) art_bkmask_normal)[(i << 2) + j] = 0xff;
					((UBYTE *) art_lummask_reverse)[((255 - i) << 2) + j] = 0x0f;
					((UBYTE *) art_bkmask_reverse)[((255 - i) << 2) + j] = 0xf0;
					continue;
				}
			}
			else if (q & 0x40) {
				if (q & 0x10)
					goto colpf1_pixel;			/* x111x */
				else if (q & 0x80) {
					if (q & 0x08)
						c = ART_BRIGHT_BROWN;	/* 11101 */
					else
						goto colpf1_pixel;		/* 11100 */
				}
				else
					c = ART_GREEN;				/* 0110x */
			}
			else if (q & 0x10) {
				if (q & 0x08) {
					if (q & 0x80)
						c = ART_BRIGHT_BROWN;	/* 00111 */
					else
						goto colpf1_pixel;		/* 10111 */
				}
				else
					c = ART_RED;				/* x0110 */
			}
			else
				c = ART_BROWN;					/* x010x */

			((UBYTE *) art_lookup_reverse)[((255 - i) << 2) + j] =
			((UBYTE *) art_lookup_normal)[(i << 2) + j] = art_colours[(j & 1) ^ c];
			continue;

			colpf1_pixel:
			((UBYTE *) art_lookup_normal)[(i << 2) + j] = art_white;
			((UBYTE *) art_lookup_reverse)[((255 - i) << 2) + j] = GTIA_COLPF2;
			((UBYTE *) art_bkmask_reverse)[((255 - i) << 2) + j] = 0xff;
			((UBYTE *) art_lummask_normal)[(i << 2) + j] = 0x0f;
			((UBYTE *) art_bkmask_normal)[(i << 2) + j] = 0xf0;
		}
	}
}