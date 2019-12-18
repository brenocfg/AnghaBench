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
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  hexstuff ;
typedef  int /*<<< orphan*/  asciistuff ;

/* Variables and functions */
 int HEXDUMP_BYTES_PER_LINE ; 
 char* HEXDUMP_HEXSTUFF_PER_LINE ; 
 int HEXDUMP_HEXSTUFF_PER_SHORT ; 
 int HEXDUMP_SHORTS_PER_LINE ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isgraph (char) ; 
 scalar_t__ isprint (char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  stdout ; 

void ascii_print_with_offset(register const u_char *cp, register u_int length) {
	register u_int i, oset = 0;
	register int s1, s2, chr = 0;
	register int nshorts;
	char hexstuff[HEXDUMP_SHORTS_PER_LINE*HEXDUMP_HEXSTUFF_PER_SHORT+1], *hsp;
	char asciistuff[HEXDUMP_BYTES_PER_LINE+1], *asp;
	char *ascii_color = "01;32";

	nshorts = length / sizeof(u_short);
	i = 0;
	hsp = hexstuff; asp = asciistuff;
	while (--nshorts >= 0) {
		s1 = *cp++;
		s2 = *cp++;
		(void)snprintf(hsp, sizeof(hexstuff) - (hsp - hexstuff),
							" %02x%02x", s1, s2);
		hsp += HEXDUMP_HEXSTUFF_PER_SHORT;
		*(asp++) = s1;
		*(asp++) = s2;
		if (++i >= HEXDUMP_SHORTS_PER_LINE) {
			*hsp = *asp = '\0';
			(void)printf("\n0x%04x\t%-*s ",
			oset, HEXDUMP_HEXSTUFF_PER_LINE,
			hexstuff);
			for (chr = 0; chr < sizeof(asciistuff) - 1; chr++) {
				if (isprint(asciistuff[chr])) {
					(void)printf("\33[%sm", ascii_color);
					(void)printf("%c", asciistuff[chr]);
					fputs("\33[00m", stdout);
				} else {
					(void)printf(".");
				}
			}
			i = 0; hsp = hexstuff; asp = asciistuff;
			oset += HEXDUMP_BYTES_PER_LINE;
		}
	}
	if (length & 1) {
		s1 = *cp++;
		(void)snprintf(hsp, sizeof(hexstuff) - (hsp - hexstuff),
							" %02x", s1);
		hsp += 3;
		*(asp++) = s1;
		++i;
	}
	if (i > 0) {
		*hsp = *asp = '\0';
		(void)printf("\n0x%04x\t%-*s ",
						oset, HEXDUMP_HEXSTUFF_PER_LINE,
						hexstuff);
		for (chr = 0; chr < sizeof(asciistuff) - 1 && asciistuff[chr] != '\0'; chr++) {
			if (isgraph(asciistuff[chr])) {
				(void)printf("\33[%sm", ascii_color);
				(void)printf("%c", asciistuff[chr]);
				fputs("\33[00m", stdout);
			} else {
				(void)printf(".");
			}
		}
	}
}