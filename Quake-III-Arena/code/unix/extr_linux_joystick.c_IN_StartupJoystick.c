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
struct js_event {int type; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_2__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  JSIOCGAXES ; 
 int /*<<< orphan*/  JSIOCGBUTTONS ; 
 int /*<<< orphan*/  JSIOCGNAME (int) ; 
 int JS_EVENT_INIT ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int PATH_MAX ; 
 TYPE_1__* in_joystick ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char*) ; 
 int joy_fd ; 
 int open (char*,int) ; 
 int read (int,struct js_event*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void IN_StartupJoystick( void )
{
  int i = 0;

  joy_fd = -1;

  if( !in_joystick->integer ) {
    Com_Printf( "Joystick is not active.\n" );
    return;
  }

  for( i = 0; i < 4; i++ ) {
    char filename[PATH_MAX];

    snprintf( filename, PATH_MAX, "/dev/js%d", i );

    joy_fd = open( filename, O_RDONLY | O_NONBLOCK );

    if( joy_fd != -1 ) {
      struct js_event event;
      char axes = 0;
      char buttons = 0;
      char name[128];
      int n = -1;

      Com_Printf( "Joystick %s found\n", filename );

      /* Get rid of initialization messages. */
      do {
	n = read( joy_fd, &event, sizeof( event ) );

	if( n == -1 ) {
	  break;
	}

      } while( ( event.type & JS_EVENT_INIT ) );

      /* Get joystick statistics. */
      ioctl( joy_fd, JSIOCGAXES, &axes );
      ioctl( joy_fd, JSIOCGBUTTONS, &buttons );

      if( ioctl( joy_fd, JSIOCGNAME( sizeof( name ) ), name ) < 0 ) {
	strncpy( name, "Unknown", sizeof( name ) );
      }

      Com_Printf( "Name:    %s\n", name );
      Com_Printf( "Axes:    %d\n", axes );
      Com_Printf( "Buttons: %d\n", buttons );

      /* Our work here is done. */
      return;
    }

  }

  /* No soup for you. */
  if( joy_fd == -1 ) {
    Com_Printf( "No joystick found.\n" );
    return;
  }

}