#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int state; int /*<<< orphan*/  filename; } ;
struct TYPE_3__ {int type; int state; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int CARTRIDGE_NONE ; 
 TYPE_2__ CARTRIDGE_main ; 
 TYPE_1__ CARTRIDGE_piggyback ; 
 int /*<<< orphan*/  StateSav_SaveFNAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StateSav_SaveINT (int*,int) ; 

void CARTRIDGE_StateSave(void)
{
	int cart_save = CARTRIDGE_main.type;
	
	if (CARTRIDGE_piggyback.type != CARTRIDGE_NONE)
		/* Save the cart type as negative, to indicate to CARTStateRead that there is a 
		   second cartridge */
		cart_save = -cart_save;
	
	/* Save the cartridge type, or CARTRIDGE_NONE if there isn't one...*/
	StateSav_SaveINT(&cart_save, 1);
	if (CARTRIDGE_main.type != CARTRIDGE_NONE) {
		StateSav_SaveFNAME(CARTRIDGE_main.filename);
		StateSav_SaveINT(&CARTRIDGE_main.state, 1);
	}

	if (CARTRIDGE_piggyback.type != CARTRIDGE_NONE) {
		/* Save the second cartridge type and name*/
		StateSav_SaveINT(&CARTRIDGE_piggyback.type, 1);
		StateSav_SaveFNAME(CARTRIDGE_piggyback.filename);
		StateSav_SaveINT(&CARTRIDGE_piggyback.state, 1);
	}
}