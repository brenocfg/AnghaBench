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
typedef  int /*<<< orphan*/  UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  POKEYSND_Update_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Update_synchronized_sound () ; 

void POKEYSND_Update(UWORD addr, UBYTE val, UBYTE chip, UBYTE gain)
{
#ifdef SYNCHRONIZED_SOUND
    Update_synchronized_sound();
#endif /* SYNCHRONIZED_SOUND */
	POKEYSND_Update_ptr(addr, val, chip, gain);
}