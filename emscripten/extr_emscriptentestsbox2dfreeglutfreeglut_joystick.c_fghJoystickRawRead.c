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
struct TYPE_3__ {int num_axes; scalar_t__ error; } ;
typedef  TYPE_1__ SFG_Joystick ;

/* Variables and functions */

__attribute__((used)) static void fghJoystickRawRead( SFG_Joystick* joy, int* buttons, float* axes )
{
#if TARGET_HOST_MS_WINDOWS && !defined(_WIN32_WCE)
    MMRESULT status;
#else
    int status;
#endif

#if defined(__FreeBSD__) || defined(__NetBSD__)
    int len;
#endif

    int i;

    /* Defaults */
    if( buttons )
        *buttons = 0;

    if( axes )
        for( i = 0; i < joy->num_axes; i++ )
            axes[ i ] = 1500.0f;

    if( joy->error )
        return;

#if TARGET_HOST_MACINTOSH
    if ( buttons )
    {
        *buttons = 0;

        for ( i = 0; i < joy->num_buttons; i++ )
        {
            UInt32 state;
            int err = ISpElement_GetSimpleState ( isp_elem [ i + isp_num_axis ], &state);
            ISP_CHECK_ERR(err)

            *buttons |= state << i;
        }
    }

    if ( axes )
    {
        for ( i = 0; i < joy->num_axes; i++ )
        {
            UInt32 state;
            int err = ISpElement_GetSimpleState ( isp_elem [ i ], &state );
            ISP_CHECK_ERR(err)

            axes [i] = (float) state;
        }
    }
#endif

#if TARGET_HOST_MAC_OSX
    if ( buttons != NULL )
    {
        *buttons = 0;

        for ( i = 0; i < joy->num_buttons; i++ )
        {
            IOHIDEventStruct hidEvent;
            (*(joy->hidDev))->getElementValue ( joy->hidDev, buttonCookies[i], &hidEvent );
            if ( hidEvent.value )
                *buttons |= 1 << i;
        }
    }

    if ( axes != NULL )
    {
        for ( i = 0; i < joy->num_axes; i++ )
        {
            IOHIDEventStruct hidEvent;
            (*(joy->hidDev))->getElementValue ( joy->hidDev, axisCookies[i], &hidEvent );
            axes[i] = hidEvent.value;
        }
    }
#endif

#if TARGET_HOST_MS_WINDOWS && !defined(_WIN32_WCE)
    status = joyGetPosEx( joy->js_id, &joy->js );

    if ( status != JOYERR_NOERROR )
    {
        joy->error = GL_TRUE;
        return;
    }

    if ( buttons )
        *buttons = joy->js.dwButtons;

    if ( axes )
    {
        /*
         * WARNING - Fall through case clauses!!
         */
        switch ( joy->num_axes )
        {
        case 8:
            /* Generate two POV axes from the POV hat angle.
             * Low 16 bits of js.dwPOV gives heading (clockwise from ahead) in
             *   hundredths of a degree, or 0xFFFF when idle.
             */
            if ( ( joy->js.dwPOV & 0xFFFF ) == 0xFFFF )
            {
              axes [ 6 ] = 0.0;
              axes [ 7 ] = 0.0;
            }
            else
            {
              /* This is the contentious bit: how to convert angle to X/Y.
               *    wk: I know of no define for PI that we could use here:
               *    SG_PI would pull in sg, M_PI is undefined for MSVC
               * But the accuracy of the value of PI is very unimportant at
               * this point.
               */
              float s = (float) sin ( ( joy->js.dwPOV & 0xFFFF ) * ( 0.01 * 3.1415926535f / 180.0f ) );
              float c = (float) cos ( ( joy->js.dwPOV & 0xFFFF ) * ( 0.01 * 3.1415926535f / 180.0f ) );

              /* Convert to coordinates on a square so that North-East
               * is (1,1) not (.7,.7), etc.
               * s and c cannot both be zero so we won't divide by zero.
               */
              if ( fabs ( s ) < fabs ( c ) )
              {
                axes [ 6 ] = ( c < 0.0 ) ? -s/c  : s/c ;
                axes [ 7 ] = ( c < 0.0 ) ? -1.0f : 1.0f;
              }
              else
              {
                axes [ 6 ] = ( s < 0.0 ) ? -1.0f : 1.0f;
                axes [ 7 ] = ( s < 0.0 ) ? -c/s  : c/s ;
              }
            }

        case 6: axes[5] = (float) joy->js.dwVpos;
        case 5: axes[4] = (float) joy->js.dwUpos;
        case 4: axes[3] = (float) joy->js.dwRpos;
        case 3: axes[2] = (float) joy->js.dwZpos;
        case 2: axes[1] = (float) joy->js.dwYpos;
        case 1: axes[0] = (float) joy->js.dwXpos;
        }
    }
#endif

#if TARGET_HOST_POSIX_X11
#    if defined(__FreeBSD__) || defined(__NetBSD__)
    if ( joy->os->is_analog )
    {
        int status = read ( joy->os->fd, &joy->os->ajs, sizeof(joy->os->ajs) );
        if ( status != sizeof(joy->os->ajs) ) {
            perror ( joy->os->fname );
            joy->error = GL_TRUE;
            return;
        }
        if ( buttons != NULL )
            *buttons = ( joy->os->ajs.b1 ? 1 : 0 ) | ( joy->os->ajs.b2 ? 2 : 0 );

        if ( axes != NULL )
        {
            axes[0] = (float) joy->os->ajs.x;
            axes[1] = (float) joy->os->ajs.y;
        }

        return;
    }

#        ifdef HAVE_USB_JS
    while ( ( len = read ( joy->os->fd, joy->os->hid_data_buf, joy->os->hid_dlen ) ) == joy->os->hid_dlen )
    {
        struct hid_item *h;

        for  ( h = joy->os->hids; h; h = h->next )
        {
            int d = hid_get_data ( joy->os->hid_data_buf, h );

            int page = HID_PAGE ( h->usage );
            int usage = HID_USAGE ( h->usage );

            if ( page == HUP_GENERIC_DESKTOP )
            {
                int i;
                for ( i = 0; i < joy->num_axes; i++ )
                    if (joy->os->axes_usage[i] == usage)
                    {
                        if (usage == HUG_HAT_SWITCH)
                        {
                            if (d < 0 || d > 8)
                                d = 0;  /* safety */
                            joy->os->cache_axes[i] = (float)hatmap_x[d];
                            joy->os->cache_axes[i + 1] = (float)hatmap_y[d];
                        }
                        else
                        {
                            joy->os->cache_axes[i] = (float)d;
                        }
                        break;
                    }
            }
            else if (page == HUP_BUTTON)
            {
               if (usage > 0 && usage < _JS_MAX_BUTTONS + 1)
               {
                   if (d)
                       joy->os->cache_buttons |=  (1 << ( usage - 1 ));
                   else
                       joy->os->cache_buttons &= ~(1 << ( usage - 1 ));
               }
            }
        }
    }
#if HAVE_ERRNO
    if ( len < 0 && errno != EAGAIN )
#else
    if ( len < 0 )
#endif
    {
        perror( joy->os->fname );
        joy->error = 1;
    }
    if ( buttons != NULL ) *buttons = joy->os->cache_buttons;
    if ( axes    != NULL )
        memcpy ( axes, joy->os->cache_axes, sizeof(float) * joy->num_axes );
#        endif
#    endif

#    ifdef JS_NEW

    while ( 1 )
    {
        status = read ( joy->fd, &joy->js, sizeof(struct js_event) );

        if ( status != sizeof( struct js_event ) )
        {
#if HAVE_ERRNO
            if ( errno == EAGAIN )
            {
                /* Use the old values */
                if ( buttons )
                    *buttons = joy->tmp_buttons;
                if ( axes )
                    memcpy( axes, joy->tmp_axes,
                            sizeof( float ) * joy->num_axes );
                return;
            }
#endif

            fgWarning ( "%s", joy->fname );
            joy->error = GL_TRUE;
            return;
        }

        switch ( joy->js.type & ~JS_EVENT_INIT )
        {
        case JS_EVENT_BUTTON:
            if( joy->js.value == 0 ) /* clear the flag */
                joy->tmp_buttons &= ~( 1 << joy->js.number );
            else
                joy->tmp_buttons |= ( 1 << joy->js.number );
            break;

        case JS_EVENT_AXIS:
            if ( joy->js.number < joy->num_axes )
            {
                joy->tmp_axes[ joy->js.number ] = ( float )joy->js.value;

                if( axes )
                    memcpy( axes, joy->tmp_axes, sizeof(float) * joy->num_axes );
            }
            break;

        default:
            fgWarning ( "PLIB_JS: Unrecognised /dev/js return!?!" );

            /* use the old values */

            if ( buttons != NULL ) *buttons = joy->tmp_buttons;
            if ( axes    != NULL )
                memcpy ( axes, joy->tmp_axes, sizeof(float) * joy->num_axes );

            return;
        }

        if( buttons )
            *buttons = joy->tmp_buttons;
    }
#    else

    status = read( joy->fd, &joy->js, JS_RETURN );

    if ( status != JS_RETURN )
    {
        fgWarning( "%s", joy->fname );
        joy->error = GL_TRUE;
        return;
    }

    if ( buttons )
#        if defined( __FreeBSD__ ) || defined( __NetBSD__ )
        *buttons = ( joy->js.b1 ? 1 : 0 ) | ( joy->js.b2 ? 2 : 0 );  /* XXX Should not be here -- BSD is handled earlier */
#        else
        *buttons = joy->js.buttons;
#        endif

    if ( axes )
    {
        axes[ 0 ] = (float) joy->js.x;
        axes[ 1 ] = (float) joy->js.y;
    }
#    endif
#endif
}