#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* data; scalar_t__ found; } ;
struct TYPE_9__ {int ID; } ;
typedef  TYPE_1__ SFG_Window ;
typedef  TYPE_2__ SFG_Enumerator ;

/* Variables and functions */
 scalar_t__ GL_TRUE ; 
 int /*<<< orphan*/  fgEnumSubWindows (TYPE_1__*,void (*) (TYPE_1__*,TYPE_2__*),TYPE_2__*) ; 

__attribute__((used)) static void fghcbWindowByID( SFG_Window *window, SFG_Enumerator *enumerator )
{
    /* Make sure we do not overwrite our precious results... */
    if( enumerator->found )
        return;

    /* Check the window's handle. Hope this works. Looks ugly. That's for sure. */
    if( window->ID == *( int *)(enumerator->data) )
    {
        enumerator->found = GL_TRUE;
        enumerator->data = window;

        return;
    }

    /* Otherwise, check this window's children */
    fgEnumSubWindows( window, fghcbWindowByID, enumerator );
}