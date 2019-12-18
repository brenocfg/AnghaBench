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
 int* POKEY_AUDCTL ; 
 int /*<<< orphan*/  POKEY_POLY17_SIZE ; 
 int POKEY_POLY9 ; 
 int /*<<< orphan*/  POKEY_POLY9_SIZE ; 
 int /*<<< orphan*/  random_scanline_counter ; 

void POKEY_Frame(void)
{
	random_scanline_counter %= (POKEY_AUDCTL[0] & POKEY_POLY9) ? POKEY_POLY9_SIZE : POKEY_POLY17_SIZE;
}