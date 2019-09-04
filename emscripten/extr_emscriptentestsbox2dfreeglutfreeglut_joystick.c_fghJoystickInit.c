#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  error; scalar_t__ num_buttons; scalar_t__ num_axes; } ;
typedef  TYPE_1__ SFG_Joystick ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TRUE ; 
 int MAX_NUM_JOYSTICKS ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fgError (char*,...) ; 
 TYPE_1__** fgJoystick ; 
 int /*<<< orphan*/  fghJoystickOpen (TYPE_1__*) ; 

__attribute__((used)) static void fghJoystickInit( int ident )
{
    if( ident >= MAX_NUM_JOYSTICKS )
      fgError( "Too large a joystick number: %d", ident );

    if( fgJoystick[ ident ] )
        fgError( "illegal attempt to initialize joystick device again" );

    fgJoystick[ ident ] =
        ( SFG_Joystick * )calloc( sizeof( SFG_Joystick ), 1 );

    /* Set defaults */
    fgJoystick[ ident ]->num_axes = fgJoystick[ ident ]->num_buttons = 0;
    fgJoystick[ ident ]->error = GL_TRUE;

#if TARGET_HOST_MACINTOSH
    fgJoystick[ ident ]->id = ident;
    snprintf( fgJoystick[ ident ]->fname, sizeof(fgJoystick[ ident ]->fname), "/dev/js%d", ident ); /* FIXME */
    fgJoystick[ ident ]->error = GL_FALSE;
#endif

#if TARGET_HOST_MAC_OSX
    fgJoystick[ ident ]->id = ident;
    fgJoystick[ ident ]->error = GL_FALSE;
    fgJoystick[ ident ]->num_axes = 0;
    fgJoystick[ ident ]->num_buttons = 0;

    if( numDevices < 0 )
    {
        /* do first-time init (since we can't over-ride jsInit, hmm */
        numDevices = 0;

        mach_port_t masterPort;
        IOReturn rv = IOMasterPort( bootstrap_port, &masterPort );
        if( rv != kIOReturnSuccess )
        {
            fgWarning( "error getting master Mach port" );
            return;
        }
        fghJoystickFindDevices( masterPort );
    }

    if ( ident >= numDevices )
    {
        fgJoystick[ ident ]->error = GL_TRUE;
        return;
    }

    /* get the name now too */
    CFDictionaryRef properties = getCFProperties( ioDevices[ ident ] );
    CFTypeRef ref = CFDictionaryGetValue( properties,
                                          CFSTR( kIOHIDProductKey ) );
    if (!ref)
        ref = CFDictionaryGetValue(properties, CFSTR( "USB Product Name" ) );

    if( !ref ||
        !CFStringGetCString( ( CFStringRef )ref, name, 128,
                             CFStringGetSystemEncoding( ) ) )
    {
        fgWarning( "error getting device name" );
        name[ 0 ] = '\0';
    }
#endif

#if TARGET_HOST_MS_WINDOWS && !defined(_WIN32_WCE)
    switch( ident )
    {
    case 0:
        fgJoystick[ ident ]->js_id = JOYSTICKID1;
        fgJoystick[ ident ]->error = GL_FALSE;
        break;
    case 1:
        fgJoystick[ ident ]->js_id = JOYSTICKID2;
        fgJoystick[ ident ]->error = GL_FALSE;
        break;
    default:
        fgJoystick[ ident ]->num_axes = 0;
        fgJoystick[ ident ]->error = GL_TRUE;
        return;
    }
#endif

#if TARGET_HOST_POSIX_X11
#    if defined( __FreeBSD__ ) || defined( __NetBSD__ )
    fgJoystick[ ident ]->id = ident;
    fgJoystick[ ident ]->error = GL_FALSE;

    fgJoystick[ ident ]->os = calloc( 1, sizeof( struct os_specific_s ) );
    memset( fgJoystick[ ident ]->os, 0, sizeof( struct os_specific_s ) );
    if( ident < USB_IDENT_OFFSET )
        fgJoystick[ ident ]->os->is_analog = 1;
    if( fgJoystick[ ident ]->os->is_analog )
        snprintf( fgJoystick[ ident ]->os->fname, sizeof(fgJoystick[ ident ]->os->fname), "%s%d", AJSDEV, ident );
    else
        snprintf( fgJoystick[ ident ]->os->fname, sizeof(fgJoystick[ ident ]->os->fname), "%s%d", UHIDDEV,
                 ident - USB_IDENT_OFFSET );
#    elif defined( __linux__ )
    fgJoystick[ ident ]->id = ident;
    fgJoystick[ ident ]->error = GL_FALSE;

    snprintf( fgJoystick[ident]->fname, sizeof(fgJoystick[ident]->fname), "/dev/input/js%d", ident );

    if( access( fgJoystick[ ident ]->fname, F_OK ) != 0 )
        snprintf( fgJoystick[ ident ]->fname, sizeof(fgJoystick[ ident ]->fname), "/dev/js%d", ident );
#    endif
#endif

    fghJoystickOpen( fgJoystick[ ident  ] );
}