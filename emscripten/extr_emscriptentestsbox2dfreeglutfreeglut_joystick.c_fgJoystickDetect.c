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
struct TYPE_4__ {int /*<<< orphan*/  error; } ;
struct TYPE_3__ {int /*<<< orphan*/  JoysticksInitialised; } ;

/* Variables and functions */
 int MAX_NUM_JOYSTICKS ; 
 int /*<<< orphan*/  fgInitialiseJoysticks () ; 
 TYPE_2__** fgJoystick ; 
 TYPE_1__ fgState ; 

int fgJoystickDetect( void )
{
    int ident;

    fgInitialiseJoysticks ();

    if ( !fgState.JoysticksInitialised )
        return 0;

    for( ident=0; ident<MAX_NUM_JOYSTICKS; ident++ )
        if( fgJoystick[ident] && !fgJoystick[ident]->error )
            return 1;

    return 0;
}