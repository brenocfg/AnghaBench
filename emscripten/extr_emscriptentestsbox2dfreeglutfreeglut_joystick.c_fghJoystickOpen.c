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
struct TYPE_3__ {char* name; scalar_t__ num_buttons; scalar_t__ num_axes; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ SFG_Joystick ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void fghJoystickOpen( SFG_Joystick* joy )
{
    int i = 0;
#if TARGET_HOST_MACINTOSH
    OSStatus err;
#endif
#if TARGET_HOST_MAC_OSX
        IOReturn rv;
        SInt32 score;
        IOCFPlugInInterface **plugin;

        HRESULT pluginResult;

        CFDictionaryRef props;
    CFTypeRef topLevelElement;
#endif
#if TARGET_HOST_POSIX_X11
#    if defined( __FreeBSD__ ) || defined( __NetBSD__ )
       char *cp;
#    endif
#    ifdef JS_NEW
       unsigned char u;
#    else
#      if defined( __linux__ ) || TARGET_HOST_SOLARIS
         int counter = 0;
#      endif
#    endif
#endif

    /* Silence gcc, the correct #ifdefs would be too fragile... */
    (void)i;

    /*
     * Default values (for no joystick -- each conditional will reset the
     * error flag)
     */
    joy->error = TRUE;
    joy->num_axes = joy->num_buttons = 0;
    joy->name[ 0 ] = '\0';

#if TARGET_HOST_MACINTOSH
    /* XXX FIXME: get joystick name in Mac */

    err = ISpStartup( );

    if( err == noErr )
    {
#define ISP_CHECK_ERR(x) if( x != noErr ) { joy->error = GL_TRUE; return; }

        joy->error = GL_TRUE;

        /* initialize the needs structure */
        ISpNeed temp_isp_needs[ isp_num_needs ] =
        {
          { "\pX-Axis",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pY-Axis",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pZ-Axis",    128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pR-Axis",    128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pAxis   4",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pAxis   5",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pAxis   6",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pAxis   7",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },
          { "\pAxis   8",  128, 0, 0, kISpElementKind_Axis,   kISpElementLabel_None, 0, 0, 0, 0 },

          { "\pButton 0",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 1",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 2",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 3",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 4",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 5",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 6",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 7",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 8",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 9",  128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 10", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 11", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 12", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 13", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 14", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 15", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 16", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 17", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 18", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 19", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 20", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 21", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 22", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 23", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 24", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 25", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 26", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 27", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 28", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 29", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 30", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
          { "\pButton 31", 128, 0, 0, kISpElementKind_Button, kISpElementLabel_Btn_Select, 0, 0, 0, 0 },
        };

        memcpy( joy->isp_needs, temp_isp_needs, sizeof (temp_isp_needs ) );


        /* next two calls allow keyboard and mouse to emulate other input
         * devices (gamepads, joysticks, etc)
         */
        /*
          err = ISpDevices_ActivateClass ( kISpDeviceClass_Keyboard );
          ISP_CHECK_ERR(err)


          err = ISpDevices_ActivateClass ( kISpDeviceClass_Mouse );
          ISP_CHECK_ERR(err)
        */

        err = ISpElement_NewVirtualFromNeeds( joy->isp_num_needs,
                                              joy->isp_needs, joy->isp_elem,
                                              0 );
        ISP_CHECK_ERR( err )

        err = ISpInit( joy->isp_num_needs, joy->isp_needs, joy->isp_elem,
                       'freeglut', nil, 0, 128, 0 );
        ISP_CHECK_ERR( err )

        joy->num_buttons = joy->isp_num_needs - joy->isp_num_axis;
        joy->num_axes    = joy->isp_num_axis;

        for( i = 0; i < joy->num_axes; i++ )
        {
            joy->dead_band[ i ] = 0;
            joy->saturate [ i ] = 1;
            joy->center   [ i ] = kISpAxisMiddle;
            joy->max      [ i ] = kISpAxisMaximum;
            joy->min      [ i ] = kISpAxisMinimum;
        }

        joy->error = GL_FALSE;
    }
    else
        joy->num_buttons = joy->num_axes = 0;
#endif

#if TARGET_HOST_MAC_OSX
    if( joy->id >= numDevices )
    {
        fgWarning( "device index out of range in fgJoystickOpen()" );
        return;
    }

    /* create device interface */
    rv = IOCreatePlugInInterfaceForService( ioDevices[ joy->id ],
                                            kIOHIDDeviceUserClientTypeID,
                                            kIOCFPlugInInterfaceID,
                                            &plugin, &score );

    if( rv != kIOReturnSuccess )
    {
        fgWarning( "error creating plugin for io device" );
        return;
    }

    pluginResult = ( *plugin )->QueryInterface(
        plugin,
        CFUUIDGetUUIDBytes(kIOHIDDeviceInterfaceID),
        &( LPVOID )joy->hidDev
    );

    if( pluginResult != S_OK )
        fgWarning ( "QI-ing IO plugin to HID Device interface failed" );

    ( *plugin )->Release( plugin ); /* don't leak a ref */
    if( joy->hidDev == NULL )
        return;

    /* store the interface in this instance */
    rv = ( *( joy->hidDev ) )->open( joy->hidDev, 0 );
    if( rv != kIOReturnSuccess )
    {
        fgWarning( "error opening device interface");
        return;
    }

    props = getCFProperties( ioDevices[ joy->id ] );

    /* recursively enumerate all the bits */
    CFTypeRef topLevelElement =
        CFDictionaryGetValue( props, CFSTR( kIOHIDElementKey ) );
    enumerateElements( topLevelElement );

    CFRelease( props );
#endif

#if TARGET_HOST_MS_WINDOWS && !defined(_WIN32_WCE)
    joy->js.dwFlags = JOY_RETURNALL;
    joy->js.dwSize  = sizeof( joy->js );

    memset( &joy->jsCaps, 0, sizeof( joy->jsCaps ) );

    joy->error =
        ( joyGetDevCaps( joy->js_id, &joy->jsCaps, sizeof( joy->jsCaps ) ) !=
          JOYERR_NOERROR );

    if( joy->jsCaps.wNumAxes == 0 )
    {
        joy->num_axes = 0;
        joy->error = GL_TRUE;
    }
    else
    {
        /* Device name from jsCaps is often "Microsoft PC-joystick driver",
         * at least for USB.  Try to get the real name from the registry.
         */
        if ( ! fghJoystickGetOEMProductName( joy, joy->name,
                                             sizeof( joy->name ) ) )
        {
            fgWarning( "JS: Failed to read joystick name from registry" );
            strncpy( joy->name, joy->jsCaps.szPname, sizeof( joy->name ) );
        }

        /* Windows joystick drivers may provide any combination of
         * X,Y,Z,R,U,V,POV - not necessarily the first n of these.
         */
        if( joy->jsCaps.wCaps & JOYCAPS_HASPOV )
        {
            joy->num_axes = _JS_MAX_AXES;
            joy->min[ 7 ] = -1.0; joy->max[ 7 ] = 1.0;  /* POV Y */
            joy->min[ 6 ] = -1.0; joy->max[ 6 ] = 1.0;  /* POV X */
        }
        else
            joy->num_axes = 6;

        joy->min[ 5 ] = ( float )joy->jsCaps.wVmin;
        joy->max[ 5 ] = ( float )joy->jsCaps.wVmax;
        joy->min[ 4 ] = ( float )joy->jsCaps.wUmin;
        joy->max[ 4 ] = ( float )joy->jsCaps.wUmax;
        joy->min[ 3 ] = ( float )joy->jsCaps.wRmin;
        joy->max[ 3 ] = ( float )joy->jsCaps.wRmax;
        joy->min[ 2 ] = ( float )joy->jsCaps.wZmin;
        joy->max[ 2 ] = ( float )joy->jsCaps.wZmax;
        joy->min[ 1 ] = ( float )joy->jsCaps.wYmin;
        joy->max[ 1 ] = ( float )joy->jsCaps.wYmax;
        joy->min[ 0 ] = ( float )joy->jsCaps.wXmin;
        joy->max[ 0 ] = ( float )joy->jsCaps.wXmax;
    }

    /* Guess all the rest judging on the axes extremals */
    for( i = 0; i < joy->num_axes; i++ )
    {
        joy->center   [ i ] = ( joy->max[ i ] + joy->min[ i ] ) * 0.5f;
        joy->dead_band[ i ] = 0.0f;
        joy->saturate [ i ] = 1.0f;
    }
#endif

#if TARGET_HOST_POSIX_X11
#if defined( __FreeBSD__ ) || defined( __NetBSD__ )
    for( i = 0; i < _JS_MAX_AXES; i++ )
        joy->os->cache_axes[ i ] = 0.0f;

    joy->os->cache_buttons = 0;

    joy->os->fd = open( joy->os->fname, O_RDONLY | O_NONBLOCK);

#if HAVE_ERRNO
    if( joy->os->fd < 0 && errno == EACCES )
        fgWarning ( "%s exists but is not readable by you", joy->os->fname );
#endif

    joy->error =( joy->os->fd < 0 );

    if( joy->error )
        return;

    joy->num_axes = 0;
    joy->num_buttons = 0;
    if( joy->os->is_analog )
    {
        FILE *joyfile;
        char joyfname[ 1024 ];
        int noargs, in_no_axes;

        float axes [ _JS_MAX_AXES ];
        int buttons[ _JS_MAX_AXES ];

        joy->num_axes    =  2;
        joy->num_buttons = 32;

        fghJoystickRawRead( joy, buttons, axes );
        joy->error = axes[ 0 ] < -1000000000.0f;
        if( joy->error )
            return;

        snprintf( joyfname, sizeof(joyfname), "%s/.joy%drc", getenv( "HOME" ), joy->id );

        joyfile = fopen( joyfname, "r" );
        joy->error =( joyfile == NULL );
        if( joy->error )
            return;

        noargs = fscanf( joyfile, "%d%f%f%f%f%f%f", &in_no_axes,
                         &joy->min[ 0 ], &joy->center[ 0 ], &joy->max[ 0 ],
                         &joy->min[ 1 ], &joy->center[ 1 ], &joy->max[ 1 ] );
        joy->error = noargs != 7 || in_no_axes != _JS_MAX_AXES;
        fclose( joyfile );
        if( joy->error )
            return;

        for( i = 0; i < _JS_MAX_AXES; i++ )
        {
            joy->dead_band[ i ] = 0.0f;
            joy->saturate [ i ] = 1.0f;
        }

        return;    /* End of analog code */
    }

#    ifdef HAVE_USB_JS
    if( ! fghJoystickInitializeHID( joy->os, &joy->num_axes,
                                    &joy->num_buttons ) )
    {
        close( joy->os->fd );
        joy->error = GL_TRUE;
        return;
    }

    cp = strrchr( joy->os->fname, '/' );
    if( cp )
    {
        if( fghJoystickFindUSBdev( &cp[1], joy->name, sizeof( joy->name ) ) ==
            0 )
            strcpy( joy->name, &cp[1] );
    }

    if( joy->num_axes > _JS_MAX_AXES )
        joy->num_axes = _JS_MAX_AXES;

    for( i = 0; i < _JS_MAX_AXES; i++ )
    {
        /* We really should get this from the HID, but that data seems
         * to be quite unreliable for analog-to-USB converters. Punt for
         * now.
         */
        if( joy->os->axes_usage[ i ] == HUG_HAT_SWITCH )
        {
            joy->max   [ i ] = 1.0f;
            joy->center[ i ] = 0.0f;
            joy->min   [ i ] = -1.0f;
        }
        else
        {
            joy->max   [ i ] = 255.0f;
            joy->center[ i ] = 127.0f;
            joy->min   [ i ] = 0.0f;
        }

        joy->dead_band[ i ] = 0.0f;
        joy->saturate[ i ] = 1.0f;
    }
#    endif
#endif

#if defined( __linux__ ) || TARGET_HOST_SOLARIS
    /* Default for older Linux systems. */
    joy->num_axes    =  2;
    joy->num_buttons = 32;

#    ifdef JS_NEW
    for( i = 0; i < _JS_MAX_AXES; i++ )
        joy->tmp_axes[ i ] = 0.0f;

    joy->tmp_buttons = 0;
#    endif

    joy->fd = open( joy->fname, O_RDONLY );

    joy->error =( joy->fd < 0 );

    if( joy->error )
        return;

    /* Set the correct number of axes for the linux driver */
#    ifdef JS_NEW
    /* Melchior Franz's fixes for big-endian Linuxes since writing
     *  to the upper byte of an uninitialized word doesn't work.
     *  9 April 2003
     */
    ioctl( joy->fd, JSIOCGAXES, &u );
    joy->num_axes = u;
    ioctl( joy->fd, JSIOCGBUTTONS, &u );
    joy->num_buttons = u;
    ioctl( joy->fd, JSIOCGNAME( sizeof( joy->name ) ), joy->name );
    fcntl( joy->fd, F_SETFL, O_NONBLOCK );
#    endif

    /*
     * The Linux driver seems to return 512 for all axes
     * when no stick is present - but there is a chance
     * that could happen by accident - so it's gotta happen
     * on both axes for at least 100 attempts.
     *
     * PWO: shouldn't be that done somehow wiser on the kernel level?
     */
#    ifndef JS_NEW
    counter = 0;

    do
    {
        fghJoystickRawRead( joy, NULL, joy->center );
        counter++;
    } while( !joy->error &&
             counter < 100 &&
             joy->center[ 0 ] == 512.0f &&
             joy->center[ 1 ] == 512.0f );

    if ( counter >= 100 )
        joy->error = GL_TRUE;
#    endif

    for( i = 0; i < _JS_MAX_AXES; i++ )
    {
#    ifdef JS_NEW
        joy->max   [ i ] =  32767.0f;
        joy->center[ i ] =      0.0f;
        joy->min   [ i ] = -32767.0f;
#    else
        joy->max[ i ] = joy->center[ i ] * 2.0f;
        joy->min[ i ] = 0.0f;
#    endif
        joy->dead_band[ i ] = 0.0f;
        joy->saturate [ i ] = 1.0f;
    }
#endif
#endif
}