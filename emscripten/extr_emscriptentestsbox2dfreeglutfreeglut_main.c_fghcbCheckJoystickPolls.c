#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {long JoystickLastPoll; long JoystickPollRate; } ;
struct TYPE_8__ {TYPE_1__ State; } ;
typedef  TYPE_2__ SFG_Window ;
typedef  int /*<<< orphan*/  SFG_Enumerator ;

/* Variables and functions */
 long fgElapsedTime () ; 
 int /*<<< orphan*/  fgEnumSubWindows (TYPE_2__*,void (*) (TYPE_2__*,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgJoystickPollWindow (TYPE_2__*) ; 

__attribute__((used)) static void fghcbCheckJoystickPolls( SFG_Window *window,
                                     SFG_Enumerator *enumerator )
{
    long int checkTime = fgElapsedTime( );

    if( window->State.JoystickLastPoll + window->State.JoystickPollRate <=
        checkTime )
    {
#if !defined(_WIN32_WCE)
        fgJoystickPollWindow( window );
#endif /* !defined(_WIN32_WCE) */
        window->State.JoystickLastPoll = checkTime;
    }

    fgEnumSubWindows( window, fghcbCheckJoystickPolls, enumerator );
}