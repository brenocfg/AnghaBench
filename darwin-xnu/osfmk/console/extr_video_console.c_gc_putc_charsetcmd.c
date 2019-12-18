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
 int /*<<< orphan*/  ESnormal ; 
 int* gc_charset ; 
 int /*<<< orphan*/  gc_vt100state ; 

__attribute__((used)) static void
gc_putc_charsetcmd(int charset, unsigned char ch)
{
	gc_vt100state = ESnormal;

	switch (ch) {
		case 'A' :
		case 'B' :
		default:
			gc_charset[charset] = 0;
			break;
		case '0' :	/* Graphic characters */
		case '2' :
			gc_charset[charset] = 0x21;
			break;
	}

}