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
struct TYPE_2__ {scalar_t__ IdleCallback; } ;

/* Variables and functions */
 TYPE_1__ fgState ; 
 scalar_t__ fghHaveJoystick () ; 
 scalar_t__ fghHavePendingRedisplays () ; 
 long fghNextTimer () ; 

__attribute__((used)) static void fghSleepForEvents( void )
{
    long msec;

    if( fgState.IdleCallback || fghHavePendingRedisplays( ) )
        return;

    msec = fghNextTimer( );
    /* XXX Use GLUT timers for joysticks... */
    /* XXX Dumb; forces granularity to .01sec */
    if( fghHaveJoystick( ) && ( msec > 10 ) )     
        msec = 10;

#if TARGET_HOST_POSIX_X11
    /*
     * Possibly due to aggressive use of XFlush() and friends,
     * it is possible to have our socket drained but still have
     * unprocessed events.  (Or, this may just be normal with
     * X, anyway?)  We do non-trivial processing of X events
     * after the event-reading loop, in any case, so we
     * need to allow that we may have an empty socket but non-
     * empty event queue.
     */
    if( ! XPending( fgDisplay.Display ) )
    {
        fd_set fdset;
        int err;
        int socket;
        struct timeval wait;

        socket = ConnectionNumber( fgDisplay.Display );
        FD_ZERO( &fdset );
        FD_SET( socket, &fdset );
        wait.tv_sec = msec / 1000;
        wait.tv_usec = (msec % 1000) * 1000;
        err = select( socket+1, &fdset, NULL, NULL, &wait );

#if HAVE_ERRNO
        if( ( -1 == err ) && ( errno != EINTR ) )
            fgWarning ( "freeglut select() error: %d", errno );
#endif
    }
#elif TARGET_HOST_MS_WINDOWS
    MsgWaitForMultipleObjects( 0, NULL, FALSE, msec, QS_ALLINPUT );
#endif
}