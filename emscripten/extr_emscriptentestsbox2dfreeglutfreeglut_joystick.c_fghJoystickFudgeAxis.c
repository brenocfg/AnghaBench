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
struct TYPE_3__ {float* center; float* min; float* saturate; float* dead_band; float* max; } ;
typedef  TYPE_1__ SFG_Joystick ;

/* Variables and functions */

__attribute__((used)) static float fghJoystickFudgeAxis( SFG_Joystick* joy, float value, int axis )
{
    if( value < joy->center[ axis ] )
    {
        float xx = ( value - joy->center[ axis ] ) / ( joy->center[ axis ] -
                                                       joy->min[ axis ] );

        if( xx < -joy->saturate[ axis ] )
            return -1.0f;

        if( xx > -joy->dead_band [ axis ] )
            return 0.0f;

        xx = ( xx + joy->dead_band[ axis ] ) / ( joy->saturate[ axis ] -
                                                 joy->dead_band[ axis ] );

        return ( xx < -1.0f ) ? -1.0f : xx;
    }
    else
    {
        float xx = ( value - joy->center [ axis ] ) / ( joy->max[ axis ] -
                                                        joy->center[ axis ] );

        if( xx > joy->saturate[ axis ] )
            return 1.0f;

        if( xx < joy->dead_band[ axis ] )
            return 0.0f;

        xx = ( xx - joy->dead_band[ axis ] ) / ( joy->saturate[ axis ] -
                                                 joy->dead_band[ axis ] );

        return ( xx > 1.0f ) ? 1.0f : xx;
    }
}