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
 scalar_t__ sprintcl (unsigned char*,unsigned char*,int) ; 
 int sprintf (unsigned char*,char*) ; 

__attribute__((used)) static int sprintrw(unsigned char *outaddr, unsigned char *addr,
		    unsigned int len)
{
	int hl, inl, c, cx;

	hl = sprintf(outaddr, "	   ");
	inl = 0;
	for (c = 0; c < (len / 16); c++) {
		hl += sprintcl(outaddr+hl, addr+inl, 16);
		inl += 16;
	}
	cx = len%16;
	if (cx) {
		hl += sprintcl(outaddr+hl, addr+inl, cx);
		inl += cx;
	}
	hl += sprintf(outaddr+hl, "\n");
	return hl;
}