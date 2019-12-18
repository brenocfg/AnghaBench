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
struct TYPE_3__ {scalar_t__ type; scalar_t__ data1; } ;
typedef  TYPE_1__ event_t ;

/* Variables and functions */
 int /*<<< orphan*/  I_Error (char*) ; 
 int I_GetTime () ; 
 int /*<<< orphan*/  I_StartTic () ; 
 scalar_t__ KEY_ESCAPE ; 
 int MAXEVENTS ; 
 scalar_t__ ev_keydown ; 
 int eventhead ; 
 TYPE_1__* events ; 
 int eventtail ; 

void CheckAbort (void)
{
    event_t *ev;
    int		stoptic;
	
    stoptic = I_GetTime () + 2; 
    while (I_GetTime() < stoptic) 
	I_StartTic (); 
	
    I_StartTic ();
    for ( ; eventtail != eventhead 
	      ; eventtail = (++eventtail)&(MAXEVENTS-1) ) 
    { 
	ev = &events[eventtail]; 
	if (ev->type == ev_keydown && ev->data1 == KEY_ESCAPE)
	    I_Error ("Network game synchronization aborted.");
    } 
}