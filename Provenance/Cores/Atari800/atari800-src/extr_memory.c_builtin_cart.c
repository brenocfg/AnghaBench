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
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ Atari800_builtin_basic ; 
 scalar_t__ Atari800_builtin_game ; 
 int const* MEMORY_basic ; 
 int MEMORY_ram_size ; 
 int const* MEMORY_xegame ; 

__attribute__((used)) static UBYTE const * builtin_cart(UBYTE portb)
{
	/* Normally BASIC is enabled by clearing bit 1 of PORTB, but it's disabled
	   when using 576K and 1088K memory expansions, where bit 1 is used for
	   selecting extended memory bank number. */
	if (Atari800_builtin_basic
	    && (portb & 0x02) == 0
	    && ((portb & 0x10) != 0 || (MEMORY_ram_size != 576 && MEMORY_ram_size != 1088)))
		return MEMORY_basic;
	/* The builtin XEGS game is disabled when BASIC is enabled. It is enabled
	   by setting bit 6 of PORTB, but it's disabled when using 320K and larger
	   XE memory expansions, where bit 6 is used for selecting extended memory
	   bank number. */
	if (Atari800_builtin_game
	    && (portb & 0x40) == 0
	    && ((portb & 0x10) != 0 || MEMORY_ram_size < 320))
		return MEMORY_xegame;
	return NULL;
}