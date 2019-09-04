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

__attribute__((used)) static void fghRememberState( void )
{
#if TARGET_HOST_POSIX_X11

    /*
     * This highly depends on the XFree86 extensions,
     * not approved as X Consortium standards
     */
#   ifdef X_XF86VidModeGetModeLine


    /*
     * Remember the current ViewPort location of the screen to be able to
     * restore the ViewPort on LeaveGameMode():
     */
    if( !XF86VidModeGetViewPort(
             fgDisplay.Display,
             fgDisplay.Screen,
             &fgDisplay.DisplayViewPortX,
             &fgDisplay.DisplayViewPortY ) )
        fgWarning( "XF86VidModeGetViewPort failed" );

    /*
     * Remember the current pointer location before going fullscreen
     * for restoring it later:
     */
    {
        Window junk_window;
        unsigned int mask;

        XQueryPointer(
            fgDisplay.Display, fgDisplay.RootWindow,
            &junk_window, &junk_window,
            &fgDisplay.DisplayPointerX, &fgDisplay.DisplayPointerY,
            &fgDisplay.DisplayPointerX, &fgDisplay.DisplayPointerY, &mask
        );
    }

    /* Query the current display settings: */
    fgDisplay.DisplayModeValid =
      XF86VidModeGetModeLine(
        fgDisplay.Display,
        fgDisplay.Screen,
        &fgDisplay.DisplayModeClock,
        &fgDisplay.DisplayMode
    );

    if( !fgDisplay.DisplayModeValid )
            fgWarning( "XF86VidModeGetModeLine failed" );

#   else
    /*
     * XXX warning fghRememberState: missing XFree86 video mode extensions,
     * XXX game mode will not change screen resolution when activated
     */
#   endif

#elif TARGET_HOST_MS_WINDOWS

/*    DEVMODE devMode; */

    /* Grab the current desktop settings... */

/* hack to get around my stupid cross-gcc headers */
#define FREEGLUT_ENUM_CURRENT_SETTINGS -1

    EnumDisplaySettings( NULL, FREEGLUT_ENUM_CURRENT_SETTINGS,
                         &fgDisplay.DisplayMode );

    /* Make sure we will be restoring all settings needed */
    fgDisplay.DisplayMode.dmFields |=
        DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;

#endif
}