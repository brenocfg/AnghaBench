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
 int /*<<< orphan*/  PIA_PACTL ; 
 int /*<<< orphan*/  PIA_PBCTL ; 
 int /*<<< orphan*/  PIA_PORTA ; 
 int /*<<< orphan*/  PIA_PORTA_mask ; 
 int /*<<< orphan*/  PIA_PORTB ; 
 int /*<<< orphan*/  PIA_PORTB_mask ; 
 int /*<<< orphan*/  StateSav_SaveUBYTE (int /*<<< orphan*/ *,int) ; 

void PIA_StateSave(void)
{
	StateSav_SaveUBYTE( &PIA_PACTL, 1 );
	StateSav_SaveUBYTE( &PIA_PBCTL, 1 );
	StateSav_SaveUBYTE( &PIA_PORTA, 1 );
	StateSav_SaveUBYTE( &PIA_PORTB, 1 );

	StateSav_SaveUBYTE( &PIA_PORTA_mask, 1 );
	StateSav_SaveUBYTE( &PIA_PORTB_mask, 1 );
}