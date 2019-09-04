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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 unsigned char ISO_CHAR_HEIGHT ; 
 unsigned char* iso_font ; 

__attribute__((used)) static void
vc_render_char(unsigned char ch, unsigned char *renderptr, short newdepth)
{
	union {
		unsigned char  *charptr;
		unsigned short *shortptr;
		uint32_t  *longptr;
	} current; 	/* current place in rendered font, multiple types. */
	unsigned char *theChar;	/* current char in iso_font */
	int line;

	current.charptr = renderptr;
	theChar = iso_font + (ch * ISO_CHAR_HEIGHT);

	for (line = 0; line < ISO_CHAR_HEIGHT; line++) {
		unsigned char mask = 1;
		do {
			switch (newdepth) {
			case 8: 
				*current.charptr++ = (*theChar & mask) ? 0xFF : 0;
				break;
			case 16:
				*current.shortptr++ = (*theChar & mask) ? 0xFFFF : 0;
				break;

			case 30: 
			case 32: 
				*current.longptr++ = (*theChar & mask) ? 0xFFFFFFFF : 0;
				break;
			}
			mask <<= 1;
		} while (mask);	/* while the single bit drops to the right */
		theChar++;
	}
}