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
typedef  int UWORD ;
typedef  int ULONG ;

/* Variables and functions */
 int* ANTIC_cl ; 
 size_t C_PF1 ; 
 size_t C_PF2 ; 
 int* art_bkmask_normal ; 
 int* art_bkmask_reverse ; 
 int* art_curbkmask ; 
 int* art_curlummask ; 
 int* art_curtable ; 
 int* art_lookup_normal ; 
 int* art_lookup_reverse ; 
 int* art_lummask_normal ; 
 int* art_lummask_reverse ; 
 int art_normal_colpf1_save ; 
 int art_normal_colpf2_save ; 
 int art_reverse_colpf1_save ; 
 int art_reverse_colpf2_save ; 

__attribute__((used)) static void setup_art_colours(void)
{
	static UWORD *art_colpf1_save = &art_normal_colpf1_save;
	static UWORD *art_colpf2_save = &art_normal_colpf2_save;
	UWORD curlum = ANTIC_cl[C_PF1] & 0x0f0f;

	if (curlum != *art_colpf1_save || ANTIC_cl[C_PF2] != *art_colpf2_save) {
		if (curlum < (ANTIC_cl[C_PF2] & 0x0f0f)) {
			art_colpf1_save = &art_reverse_colpf1_save;
			art_colpf2_save = &art_reverse_colpf2_save;
			art_curtable = art_lookup_reverse;
			art_curlummask = art_lummask_reverse;
			art_curbkmask = art_bkmask_reverse;
		}
		else {
			art_colpf1_save = &art_normal_colpf1_save;
			art_colpf2_save = &art_normal_colpf2_save;
			art_curtable = art_lookup_normal;
			art_curlummask = art_lummask_normal;
			art_curbkmask = art_bkmask_normal;
		}
		if (curlum ^ *art_colpf1_save) {
			int i;
			ULONG new_colour = curlum ^ *art_colpf1_save;
			new_colour |= new_colour << 16;
			*art_colpf1_save = curlum;
			for (i = 0; i <= 255; i++)
				art_curtable[i] ^= art_curlummask[i] & new_colour;
		}
		if (ANTIC_cl[C_PF2] ^ *art_colpf2_save) {
			int i;
			ULONG new_colour = ANTIC_cl[C_PF2] ^ *art_colpf2_save;
			new_colour |= new_colour << 16;
			*art_colpf2_save = ANTIC_cl[C_PF2];
			for (i = 0; i <= 255; i++)
				art_curtable[i] ^= art_curbkmask[i] & new_colour;
		}

	}
}