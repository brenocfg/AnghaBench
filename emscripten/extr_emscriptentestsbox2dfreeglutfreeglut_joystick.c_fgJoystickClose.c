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

/* Variables and functions */
 int MAX_NUM_JOYSTICKS ; 
 int /*<<< orphan*/ ** fgJoystick ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void fgJoystickClose( void )
{
    int ident ;
    for( ident = 0; ident < MAX_NUM_JOYSTICKS; ident++ )
    {
        if( fgJoystick[ ident ] )
        {

#if TARGET_HOST_MACINTOSH
            ISpSuspend( );
            ISpStop( );
            ISpShutdown( );
#endif

#if TARGET_HOST_MAC_OSX
            ( *( fgJoystick[ ident ]->hidDev ) )->
                close( fgJoystick[ ident ]->hidDev );
#endif

#if TARGET_HOST_MS_WINDOWS && !defined(_WIN32_WCE)
            /* Do nothing special */
#endif

#if TARGET_HOST_POSIX_X11
#if defined( __FreeBSD__ ) || defined( __NetBSD__ )
            if( fgJoystick[ident]->os )
            {
                if( ! fgJoystick[ ident ]->error )
                    close( fgJoystick[ ident ]->os->fd );
#ifdef HAVE_USB_JS
                if( fgJoystick[ ident ]->os->hids )
                    free (fgJoystick[ ident ]->os->hids);
                if( fgJoystick[ ident ]->os->hid_data_buf )
                    free( fgJoystick[ ident ]->os->hid_data_buf );
#endif
                free( fgJoystick[ident]->os );
            }
#endif

            if( ! fgJoystick[ident]->error )
                close( fgJoystick[ ident ]->fd );
#endif

            free( fgJoystick[ ident ] );
            fgJoystick[ ident ] = NULL;
            /* show joystick has been deinitialized */
        }
    }
}