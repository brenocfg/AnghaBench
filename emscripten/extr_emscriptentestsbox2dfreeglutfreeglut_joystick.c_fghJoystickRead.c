#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_axes; scalar_t__ error; } ;
typedef  TYPE_1__ SFG_Joystick ;

/* Variables and functions */
 int _JS_MAX_AXES ; 
 float fghJoystickFudgeAxis (TYPE_1__*,float,int) ; 
 int /*<<< orphan*/  fghJoystickRawRead (TYPE_1__*,int*,float*) ; 

__attribute__((used)) static void fghJoystickRead( SFG_Joystick* joy, int* buttons, float* axes )
{
    float raw_axes[ _JS_MAX_AXES ];
    int  i;

    if( joy->error )
    {
        if( buttons )
            *buttons = 0;

        if( axes )
            for ( i=0; i<joy->num_axes; i++ )
                axes[ i ] = 0.0f;
    }

    fghJoystickRawRead( joy, buttons, raw_axes );

    if( axes )
        for( i=0; i<joy->num_axes; i++ )
            axes[ i ] = fghJoystickFudgeAxis( joy, raw_axes[ i ], i );
}