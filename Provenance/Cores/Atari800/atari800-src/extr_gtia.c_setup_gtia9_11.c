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
typedef  int ULONG ;

/* Variables and functions */
 int* ANTIC_lookup_gtia11 ; 
 int* ANTIC_lookup_gtia9 ; 
 int GTIA_COLBK ; 
 void** colour_translation_table ; 

__attribute__((used)) static void setup_gtia9_11(void) {
	int i;
#ifdef USE_COLOUR_TRANSLATION_TABLE
	UWORD temp;
	temp = colour_translation_table[GTIA_COLBK & 0xf0];
	ANTIC_lookup_gtia11[0] = ((ULONG) temp << 16) + temp;
	for (i = 1; i < 16; i++) {
		temp = colour_translation_table[GTIA_COLBK | i];
		ANTIC_lookup_gtia9[i] = ((ULONG) temp << 16) + temp;
		temp = colour_translation_table[GTIA_COLBK | (i << 4)];
		ANTIC_lookup_gtia11[i] = ((ULONG) temp << 16) + temp;
	}
#else
	ULONG count9 = 0;
	ULONG count11 = 0;
	ANTIC_lookup_gtia11[0] = ANTIC_lookup_gtia9[0] & 0xf0f0f0f0;
	for (i = 1; i < 16; i++) {
		ANTIC_lookup_gtia9[i] = ANTIC_lookup_gtia9[0] | (count9 += 0x01010101);
		ANTIC_lookup_gtia11[i] = ANTIC_lookup_gtia9[0] | (count11 += 0x10101010);
	}
#endif
}