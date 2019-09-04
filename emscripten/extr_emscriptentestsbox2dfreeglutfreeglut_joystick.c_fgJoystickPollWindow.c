#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  SFG_Window ;

/* Variables and functions */
 int /*<<< orphan*/ * FETCH_WCB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVOKE_WCB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Joystick ; 
 int MAX_NUM_JOYSTICKS ; 
 int _JS_MAX_AXES ; 
 TYPE_1__** fgJoystick ; 
 int /*<<< orphan*/  fghJoystickRead (TYPE_1__*,int*,float*) ; 
 int /*<<< orphan*/  freeglut_return_if_fail (int /*<<< orphan*/ *) ; 

void fgJoystickPollWindow( SFG_Window* window )
{
    float axes[ _JS_MAX_AXES ];
    int buttons;
    int ident;

    freeglut_return_if_fail( window );
    freeglut_return_if_fail( FETCH_WCB( *window, Joystick ) );

    for( ident = 0; ident < MAX_NUM_JOYSTICKS; ident++ )
    {
        if( fgJoystick[ident] )
        {
            fghJoystickRead( fgJoystick[ident], &buttons, axes );

            if( !fgJoystick[ident]->error )
                INVOKE_WCB( *window, Joystick,
                            ( buttons,
                              (int) ( axes[ 0 ] * 1000.0f ),
                              (int) ( axes[ 1 ] * 1000.0f ),
                              (int) ( axes[ 2 ] * 1000.0f ) )
                );
        }
    }
}