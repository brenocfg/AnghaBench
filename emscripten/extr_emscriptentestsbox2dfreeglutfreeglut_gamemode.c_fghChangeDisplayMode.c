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
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 

__attribute__((used)) static GLboolean fghChangeDisplayMode( GLboolean haveToTest )
{
    GLboolean success = GL_FALSE;
#if TARGET_HOST_POSIX_X11

    /*
     * This highly depends on the XFree86 extensions,
     * not approved as X Consortium standards
     */
#   ifdef X_XF86VidModeGetAllModeLines

    /*
     * This is also used by applcations which check modes by calling
     * glutGameModeGet(GLUT_GAME_MODE_POSSIBLE), so allow the check:
     */
    if( haveToTest || fgDisplay.DisplayModeValid )
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
            return success;
        }


        /*
         * Check every of the modes looking for one that matches our demands,
         * ignoring the refresh rate if no exact match could be found.
         */
        i = fghCheckDisplayModes( GL_TRUE, displayModesCount, displayModes );
        if( i < 0 ) {
            i = fghCheckDisplayModes( GL_FALSE, displayModesCount, displayModes );
        }
        success = ( i < 0 ) ? GL_FALSE : GL_TRUE;

        if( !haveToTest && success ) {
            if( !XF86VidModeSwitchToMode(
                     fgDisplay.Display,
                     fgDisplay.Screen,
                     displayModes[ i ] ) )
                fgWarning( "XF86VidModeSwitchToMode failed" );
        }

        XFree( displayModes );
    }

#   else

    /*
     * XXX warning fghChangeDisplayMode: missing XFree86 video mode extensions,
     * XXX game mode will not change screen resolution when activated
     */
    success = GL_TRUE;

#   endif

#elif TARGET_HOST_MS_WINDOWS

    DEVMODE  devMode;
    char *fggmstr = NULL;

    success = GL_FALSE;

    EnumDisplaySettings( NULL, -1, &devMode ); 
    devMode.dmFields |= DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;

    devMode.dmPelsWidth  = fgState.GameModeSize.X;
    devMode.dmPelsHeight = fgState.GameModeSize.Y;
    devMode.dmBitsPerPel = fgState.GameModeDepth;
    devMode.dmDisplayFrequency = fgState.GameModeRefresh;
    devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;

    switch ( ChangeDisplaySettingsEx(NULL, &devMode, NULL, haveToTest ? CDS_TEST : CDS_FULLSCREEN , NULL) )
    {
    case DISP_CHANGE_SUCCESSFUL:
        success = GL_TRUE;

        /* update vars in case if windows switched to proper mode */
        EnumDisplaySettings( NULL, FREEGLUT_ENUM_CURRENT_SETTINGS, &devMode );
        fgState.GameModeSize.X  = devMode.dmPelsWidth;        
        fgState.GameModeSize.Y  = devMode.dmPelsHeight;
        fgState.GameModeDepth   = devMode.dmBitsPerPel;
        fgState.GameModeRefresh = devMode.dmDisplayFrequency;
		break;
    case DISP_CHANGE_RESTART:
        fggmstr = "The computer must be restarted for the graphics mode to work.";
        break;
    case DISP_CHANGE_BADFLAGS:
        fggmstr = "An invalid set of flags was passed in.";
        break;
    case DISP_CHANGE_BADPARAM:
        fggmstr = "An invalid parameter was passed in. This can include an invalid flag or combination of flags.";
        break;
    case DISP_CHANGE_FAILED:
        fggmstr = "The display driver failed the specified graphics mode.";
        break;
    case DISP_CHANGE_BADMODE:
        fggmstr = "The graphics mode is not supported.";
        break;
    default:
        fggmstr = "Unknown error in graphics mode???"; /* dunno if it is possible,MSDN does not mention any other error */
        break;
    }

    if ( !success )
        fgWarning(fggmstr); /* I'd rather get info whats going on in my program than wonder about */
                            /* magic happenings behind my back, its lib for devels at last ;) */
#endif

    return success;
}