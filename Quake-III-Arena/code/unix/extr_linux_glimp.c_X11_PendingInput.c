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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int ConnectionNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QueuedAlready ; 
 scalar_t__ XEventsQueued (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XPending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dpy ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static qboolean X11_PendingInput(void) {

  assert(dpy != NULL);

  // Flush the display connection
  //  and look to see if events are queued
  XFlush( dpy );
  if ( XEventsQueued( dpy, QueuedAlready) )
  {
    return qtrue;
  }

  // More drastic measures are required -- see if X is ready to talk
  {
    static struct timeval zero_time;
    int x11_fd;
    fd_set fdset;

    x11_fd = ConnectionNumber( dpy );
    FD_ZERO(&fdset);
    FD_SET(x11_fd, &fdset);
    if ( select(x11_fd+1, &fdset, NULL, NULL, &zero_time) == 1 )
    {
      return(XPending(dpy));
    }
  }

  // Oh well, nothing is ready ..
  return qfalse;
}