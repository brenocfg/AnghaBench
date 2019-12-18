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
 int FALSE ; 
 int TRUE ; 

int Util_chrieq(char c1, char c2)
{
	switch (c1 ^ c2) {
	case 0x00:
		return TRUE;
	case 0x20:
		return (c1 >= 'A' && c1 <= 'Z') || (c1 >= 'a' && c1 <= 'z');
	default:
		return FALSE;
	}
}