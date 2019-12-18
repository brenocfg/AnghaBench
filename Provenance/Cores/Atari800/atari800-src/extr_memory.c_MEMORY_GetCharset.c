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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 scalar_t__ emuos_h ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

void MEMORY_GetCharset(UBYTE *cs)
{
	/* copy font, but change screencode order to ATASCII order */
	memcpy(cs, emuos_h + 0x200, 0x100); /* control chars */
	memcpy(cs + 0x100, emuos_h, 0x200); /* !"#$..., uppercase letters */
	memcpy(cs + 0x300, emuos_h + 0x300, 0x100); /* lowercase letters */
}