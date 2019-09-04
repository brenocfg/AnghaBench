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
struct TYPE_2__ {scalar_t__ InputDevsInitialised; } ;

/* Variables and functions */
 scalar_t__ GL_FALSE ; 
 int /*<<< orphan*/ * dialbox_port ; 
 TYPE_1__ fgState ; 
 int /*<<< orphan*/  serial_close (int /*<<< orphan*/ *) ; 

void fgInputDeviceClose( void )
{
    if ( fgState.InputDevsInitialised )
    {
        serial_close ( dialbox_port );
        dialbox_port = NULL;
        fgState.InputDevsInitialised = GL_FALSE;
    }
}