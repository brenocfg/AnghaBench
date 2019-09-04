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
struct TYPE_5__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  found; } ;
typedef  int /*<<< orphan*/  SFG_Window ;
typedef  TYPE_1__ SFG_Enumerator ;

/* Variables and functions */
 scalar_t__ FETCH_WCB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  Joystick ; 
 int /*<<< orphan*/  fgEnumSubWindows (int /*<<< orphan*/ *,void (*) (int /*<<< orphan*/ *,TYPE_1__*),TYPE_1__*) ; 

__attribute__((used)) static void fghCheckJoystickCallback( SFG_Window* w, SFG_Enumerator* e)
{
    if( FETCH_WCB( *w, Joystick ) )
    {
        e->found = GL_TRUE;
        e->data = w;
    }
    fgEnumSubWindows( w, fghCheckJoystickCallback, e );
}