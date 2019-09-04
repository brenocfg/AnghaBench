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
struct TYPE_3__ {void* data; scalar_t__ found; } ;
typedef  int /*<<< orphan*/  SFG_Window ;
typedef  TYPE_1__ SFG_Enumerator ;

/* Variables and functions */
 scalar_t__ GL_FALSE ; 
 int /*<<< orphan*/  fgEnumWindows (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fghcbWindowByID ; 

SFG_Window* fgWindowByID( int windowID )
{
    SFG_Enumerator enumerator;

    /* Uses a method very similiar for fgWindowByHandle... */
    enumerator.found = GL_FALSE;
    enumerator.data = ( void * )&windowID;
    fgEnumWindows( fghcbWindowByID, &enumerator );
    if( enumerator.found )
        return ( SFG_Window * )enumerator.data;
    return NULL;
}