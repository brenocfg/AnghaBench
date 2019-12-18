#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UBYTE ;
struct TYPE_4__ {int type; int state; } ;

/* Variables and functions */
 scalar_t__ CARTRIDGE_Insert (char*) ; 
 scalar_t__ CARTRIDGE_Insert_Second (char*) ; 
 int CARTRIDGE_NONE ; 
 TYPE_1__ CARTRIDGE_main ; 
 TYPE_1__ CARTRIDGE_piggyback ; 
 scalar_t__ CartIsPassthrough (int) ; 
 int FILENAME_MAX ; 
 int /*<<< orphan*/  MapActiveCart () ; 
 int /*<<< orphan*/  StateSav_ReadFNAME (char*) ; 
 int /*<<< orphan*/  StateSav_ReadINT (int*,int) ; 
 TYPE_1__* active_cart ; 

void CARTRIDGE_StateRead(UBYTE version)
{
	int saved_type = CARTRIDGE_NONE;
	char filename[FILENAME_MAX];

	/* Read the cart type from the file.  If there is no cart type, becaused we have
	   reached the end of the file, this will just default to CART_NONE */
	StateSav_ReadINT(&saved_type, 1);
	if (saved_type != CARTRIDGE_NONE) {
		StateSav_ReadFNAME(filename);
		if (filename[0]) {
			/* Insert the cartridge... */
			if (CARTRIDGE_Insert(filename) >= 0) {
				/* And set the type to the saved type, in case it was a raw cartridge image */
				CARTRIDGE_main.type = saved_type;
			}
		}
		if (version >= 7)
			/* Read the cartridge's state (current bank etc.). */
			StateSav_ReadINT(&CARTRIDGE_main.state, 1);
	}
	else
		CARTRIDGE_main.type = saved_type;

	if (saved_type < 0) {
		/* Minus value indicates a piggyback cartridge present. */
		CARTRIDGE_main.type = -saved_type;
	
		StateSav_ReadINT(&saved_type, 1);
		StateSav_ReadFNAME(filename);
		if (filename[0]) {
			/* Insert the cartridge... */
			if (CARTRIDGE_Insert_Second(filename) >= 0) {
				/* And set the type to the saved type, in case it was a raw cartridge image */
				CARTRIDGE_piggyback.type = saved_type;
			}
		}
		if (version >= 7)
			/* Read the cartridge's state (current bank etc.). */
			StateSav_ReadINT(&CARTRIDGE_piggyback.state, 1);
		else {
			/* Savestate version 6 explicitely stored information about
			   the active cartridge. */
			int piggyback_active;
			StateSav_ReadINT(&piggyback_active, 1);
			if (piggyback_active)
				active_cart = &CARTRIDGE_piggyback;
			else
				active_cart = &CARTRIDGE_main;
			/* The "Determine active cartridge" code below makes no
			   sense when loading ver.6 savestates, because they
			   did not store the cartridge state. */
			return;
		}
	}

	/* Determine active cartridge (main or piggyback. */
	if (CartIsPassthrough(CARTRIDGE_main.type) && (CARTRIDGE_main.state & 0x0c) == 0x08)
		active_cart = &CARTRIDGE_piggyback;
	else
		active_cart = &CARTRIDGE_main;

	MapActiveCart();
}