#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* data; scalar_t__ found; } ;
struct TYPE_10__ {scalar_t__ Handle; } ;
struct TYPE_11__ {TYPE_1__ Window; } ;
typedef  scalar_t__ SFG_WindowHandleType ;
typedef  TYPE_2__ SFG_Window ;
typedef  TYPE_3__ SFG_Enumerator ;

/* Variables and functions */
 scalar_t__ GL_TRUE ; 
 int /*<<< orphan*/  fgEnumSubWindows (TYPE_2__*,void (*) (TYPE_2__*,TYPE_3__*),TYPE_3__*) ; 

__attribute__((used)) static void fghcbWindowByHandle( SFG_Window *window,
                                 SFG_Enumerator *enumerator )
{
    if ( enumerator->found )
        return;

    /* Check the window's handle. Hope this works. Looks ugly. That's for sure. */
    if( window->Window.Handle == (SFG_WindowHandleType) (enumerator->data) )
    {
        enumerator->found = GL_TRUE;
        enumerator->data = window;

        return;
    }

    /* Otherwise, check this window's children */
    fgEnumSubWindows( window, fghcbWindowByHandle, enumerator );
}