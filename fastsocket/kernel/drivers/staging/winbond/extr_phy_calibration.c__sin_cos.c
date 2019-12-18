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
typedef  scalar_t__ s32 ;
typedef  scalar_t__ fixed ;

/* Variables and functions */
 int /*<<< orphan*/  AG_CONST ; 
 scalar_t__* Angles ; 
 scalar_t__ FIXED (int /*<<< orphan*/ ) ; 
 scalar_t__ abs (scalar_t__) ; 

void _sin_cos(s32 angle, s32 *sin, s32 *cos)
{
    fixed       X, Y, TargetAngle, CurrAngle;
    unsigned    Step;

    X=FIXED(AG_CONST);      // AG_CONST * cos(0)
    Y=0;                    // AG_CONST * sin(0)
    TargetAngle=abs(angle);
    CurrAngle=0;

    for (Step=0; Step < 12; Step++)
    {
        fixed NewX;

        if(TargetAngle > CurrAngle)
        {
            NewX=X - (Y >> Step);
            Y=(X >> Step) + Y;
            X=NewX;
            CurrAngle += Angles[Step];
        }
        else
        {
            NewX=X + (Y >> Step);
            Y=-(X >> Step) + Y;
            X=NewX;
            CurrAngle -= Angles[Step];
        }
    }

    if (angle > 0)
    {
        *cos = X;
        *sin = Y;
    }
    else
    {
        *cos = X;
        *sin = -Y;
    }
}