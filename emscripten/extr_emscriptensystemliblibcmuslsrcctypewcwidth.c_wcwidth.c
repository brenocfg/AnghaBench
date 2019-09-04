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
typedef  int wchar_t ;

/* Variables and functions */
 int* table ; 
 int* wtable ; 

int wcwidth(wchar_t wc)
{
	if (wc < 0xffU)
		return (wc+1 & 0x7f) >= 0x21 ? 1 : wc ? -1 : 0;
	if ((wc & 0xfffeffffU) < 0xfffe) {
		if ((table[table[wc>>8]*32+((wc&255)>>3)]>>(wc&7))&1)
			return 0;
		if ((wtable[wtable[wc>>8]*32+((wc&255)>>3)]>>(wc&7))&1)
			return 2;
		return 1;
	}
	if ((wc & 0xfffe) == 0xfffe)
		return -1;
	if (wc-0x20000U < 0x20000)
		return 2;
	if (wc == 0xe0001 || wc-0xe0020U < 0x5f || wc-0xe0100 < 0xef)
		return 0;
	return 1;
}