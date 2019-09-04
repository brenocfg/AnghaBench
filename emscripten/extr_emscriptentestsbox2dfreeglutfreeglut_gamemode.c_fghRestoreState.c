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

__attribute__((used)) static void fghRestoreState( void )
{
#if TARGET_HOST_POSIX_X11

#   ifdef X_XF86VidModeGetAllModeLines
    /* Restore the remembered pointer position: */
    XWarpPointer(
        fgDisplay.Display, None, fgDisplay.RootWindow, 0, 0, 0, 0,
        fgDisplay.DisplayPointerX, fgDisplay.DisplayPointerY
    );

    /*
     * This highly depends on the XFree86 extensions,
     * not approved as X Consortium standards
     */

    if( fgDisplay.DisplayModeValid )
    {
        XF86VidModeModeInfo** displayModes;
        int i, displayModesCount;

        if( !XF86VidModeGetAllModeLines(
                 fgDisplay.Display,
                 fgDisplay.Screen,
                 &displayModesCount,
                 &displayModes ) )
        {
            fgWarning( "XF86VidModeGetAllModeLines failed" );
            return;
        }


        /*
         * Check every of the modes looking for one that matches our demands.
         * If we find one, switch to it and restore the remembered viewport.
         */
        for( i = 0; i < displayModesCount; i++ )
        {
            if(displayModes[ i ]->hdisplay == fgDisplay.DisplayMode.hdisplay &&
               displayModes[ i ]->vdisplay == fgDisplay.DisplayMode.vdisplay &&
               displayModes[ i ]->dotclock == fgDisplay.DisplayModeClock )
            {
                if( !XF86VidModeSwitchToMode(
                         fgDisplay.Display,
                         fgDisplay.Screen,
                         displayModes[ i ] ) )
                {
                    fgWarning( "XF86VidModeSwitchToMode failed" );
                    break;
                }

                if( !XF86VidModeSetViewPort(
                         fgDisplay.Display,
                         fgDisplay.Screen,
                         fgDisplay.DisplayViewPortX,
                         fgDisplay.DisplayViewPortY ) )
                    fgWarning( "XF86VidModeSetViewPort failed" );


                /*
                 * For the case this would be the last X11 call the application
                 * calls exit() we've to flush the X11 output queue to have the
                 * commands sent to the X server before the application exits.
                 */
                XFlush( fgDisplay.Display );

                break;
            }
        }
        XFree( displayModes );
    }

#   else
    /*
     * XXX warning fghRestoreState: missing XFree86 video mode extensions,
     * XXX game mode will not change screen resolution when activated
     */
#   endif

#elif TARGET_HOST_MS_WINDOWS

    /* Restore the previously rememebered desktop display settings */
    ChangeDisplaySettings( &fgDisplay.DisplayMode, 0 );

#endif
}