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
 int /*<<< orphan*/  boot_text_mapped ; 
 int /*<<< orphan*/  btext_drawchar (char) ; 
 char hex_asc_hi (unsigned long) ; 
 char hex_asc_lo (unsigned long) ; 

void btext_drawhex(unsigned long v)
{
	if (!boot_text_mapped)
		return;
#ifdef CONFIG_PPC64
	btext_drawchar(hex_asc_hi(v >> 56));
	btext_drawchar(hex_asc_lo(v >> 56));
	btext_drawchar(hex_asc_hi(v >> 48));
	btext_drawchar(hex_asc_lo(v >> 48));
	btext_drawchar(hex_asc_hi(v >> 40));
	btext_drawchar(hex_asc_lo(v >> 40));
	btext_drawchar(hex_asc_hi(v >> 32));
	btext_drawchar(hex_asc_lo(v >> 32));
#endif
	btext_drawchar(hex_asc_hi(v >> 24));
	btext_drawchar(hex_asc_lo(v >> 24));
	btext_drawchar(hex_asc_hi(v >> 16));
	btext_drawchar(hex_asc_lo(v >> 16));
	btext_drawchar(hex_asc_hi(v >> 8));
	btext_drawchar(hex_asc_lo(v >> 8));
	btext_drawchar(hex_asc_hi(v));
	btext_drawchar(hex_asc_lo(v));
	btext_drawchar(' ');
}