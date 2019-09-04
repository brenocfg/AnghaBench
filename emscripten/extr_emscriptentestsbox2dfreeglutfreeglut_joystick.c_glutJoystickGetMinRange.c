#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_axes; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREEGLUT_EXIT_IF_NOT_INITIALISED (char*) ; 
 TYPE_1__** fgJoystick ; 
 int /*<<< orphan*/  memcpy (float*,int /*<<< orphan*/ ,int) ; 

void glutJoystickGetMinRange( int ident, float *axes )
{
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutJoystickGetMinRange" );
    memcpy( axes, fgJoystick[ ident ]->min,
            fgJoystick[ ident ]->num_axes * sizeof( float ) );
}