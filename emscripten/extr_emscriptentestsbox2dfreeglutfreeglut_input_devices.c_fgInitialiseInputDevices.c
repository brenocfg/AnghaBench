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
struct TYPE_2__ {scalar_t__ InputDevsInitialised; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIAL_INITIALIZE ; 
 scalar_t__ GL_TRUE ; 
 int /*<<< orphan*/  dialbox_port ; 
 TYPE_1__ fgState ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  glutTimerFunc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_dials ; 
 int /*<<< orphan*/  serial_open (char const*) ; 
 int /*<<< orphan*/  serial_putchar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fgInitialiseInputDevices ( void )
{
    if( !fgState.InputDevsInitialised )
    {
      /* will return true for VC8 (VC2005) and higher */
#if TARGET_HOST_MS_WINDOWS && ( _MSC_VER >= 1400 ) && HAVE_ERRNO
        char *dial_device=NULL;
        size_t sLen;
        errno_t err = _dupenv_s( &dial_device, &sLen, "GLUT_DIALS_SERIAL" );
        if (err)
            fgError("Error getting GLUT_DIALS_SERIAL environment variable");
#else
        const char *dial_device=NULL;
        dial_device = getenv ( "GLUT_DIALS_SERIAL" );
#endif
#if TARGET_HOST_MS_WINDOWS
        if (!dial_device){
            static char devname[256];
            DWORD size=sizeof(devname);
            DWORD type = REG_SZ;
            HKEY key;
            if (RegOpenKeyA(HKEY_LOCAL_MACHINE,"SOFTWARE\\FreeGLUT",&key)==ERROR_SUCCESS) {
                if (RegQueryValueExA(key,"DialboxSerialPort",NULL,&type,(LPBYTE)devname,&size)==ERROR_SUCCESS){
                    dial_device=devname;
                }
                RegCloseKey(key);
            }
        }
#endif
        if ( !dial_device ) return;
        if ( !( dialbox_port = serial_open ( dial_device ) ) ) return;
      /* will return true for VC8 (VC2005) and higher */
#if TARGET_HOST_MS_WINDOWS && ( _MSC_VER >= 1400 ) && HAVE_ERRNO
        free ( dial_device );  dial_device = NULL;  /* dupenv_s allocates a string that we must free */
#endif
        serial_putchar(dialbox_port,DIAL_INITIALIZE);
        glutTimerFunc ( 10, poll_dials, 0 );
        fgState.InputDevsInitialised = GL_TRUE;
    }
}