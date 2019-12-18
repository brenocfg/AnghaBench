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
struct js_event {int type; int number; int value; } ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_2__ {float value; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int JS_EVENT_AXIS ; 
 int JS_EVENT_BUTTON ; 
 scalar_t__ K_JOY1 ; 
 int /*<<< orphan*/  SE_KEY ; 
 int /*<<< orphan*/  Sys_QueEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int joy_fd ; 
 scalar_t__* joy_keys ; 
 TYPE_1__* joy_threshold ; 
 int qfalse ; 
 int qtrue ; 
 int read (int,struct js_event*,int) ; 

void IN_JoyMove( void )
{
  /* Store instantaneous joystick state. Hack to get around
   * event model used in Linux joystick driver.
	 */
  static int axes_state[16];
  /* Old bits for Quake-style input compares. */
  static unsigned int old_axes = 0;
  /* Our current goodies. */
  unsigned int axes = 0;
  int i = 0;

  if( joy_fd == -1 ) {
    return;
  }

  /* Empty the queue, dispatching button presses immediately
	 * and updating the instantaneous state for the axes.
	 */
  do {
    int n = -1;
    struct js_event event;

    n = read( joy_fd, &event, sizeof( event ) );

    if( n == -1 ) {
      /* No error, we're non-blocking. */
      break;
    }

    if( event.type & JS_EVENT_BUTTON ) {
      Sys_QueEvent( 0, SE_KEY, K_JOY1 + event.number, event.value, 0, NULL );
    } else if( event.type & JS_EVENT_AXIS ) {

      if( event.number >= 16 ) {
	continue;
      }

      axes_state[event.number] = event.value;
    } else {
      Com_Printf( "Unknown joystick event type\n" );
    }

  } while( 1 );


  /* Translate our instantaneous state to bits. */
  for( i = 0; i < 16; i++ ) {
    float f = ( (float) axes_state[i] ) / 32767.0f;

    if( f < -joy_threshold->value ) {
      axes |= ( 1 << ( i * 2 ) );
    } else if( f > joy_threshold->value ) {
      axes |= ( 1 << ( ( i * 2 ) + 1 ) );
    }

  }

  /* Time to update axes state based on old vs. new. */
  for( i = 0; i < 16; i++ ) {

    if( ( axes & ( 1 << i ) ) && !( old_axes & ( 1 << i ) ) ) {
      Sys_QueEvent( 0, SE_KEY, joy_keys[i], qtrue, 0, NULL );
    }

    if( !( axes & ( 1 << i ) ) && ( old_axes & ( 1 << i ) ) ) {
      Sys_QueEvent( 0, SE_KEY, joy_keys[i], qfalse, 0, NULL );
    }
  }

  /* Save for future generations. */
  old_axes = axes;
}