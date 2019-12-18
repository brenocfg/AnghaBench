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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static inline u16 mda_convert_attr(u16 ch)
{
	u16 attr = 0x0700;

	/* Underline and reverse-video are mutually exclusive on MDA.
	 * Since reverse-video is used for cursors and selected areas,
	 * it takes precedence. 
	 */

	if (ch & 0x0800)	attr = 0x7000;	/* reverse */
	else if (ch & 0x0400)	attr = 0x0100;	/* underline */

	return ((ch & 0x0200) << 2) | 		/* intensity */ 
		(ch & 0x8000) |			/* blink */ 
		(ch & 0x00ff) | attr;
}