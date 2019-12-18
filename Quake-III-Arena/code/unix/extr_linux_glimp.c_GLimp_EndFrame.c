#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {int /*<<< orphan*/  string; } ;
struct TYPE_3__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  QGL_EnableLogging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpy ; 
 int /*<<< orphan*/  qglXSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* r_drawBuffer ; 
 TYPE_1__* r_logFile ; 
 scalar_t__ stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win ; 

void GLimp_EndFrame (void)
{
  // don't flip if drawing to front buffer
  if ( stricmp( r_drawBuffer->string, "GL_FRONT" ) != 0 )
  {
    qglXSwapBuffers(dpy, win);
  }

  // check logging
  QGL_EnableLogging( (qboolean)r_logFile->integer ); // bk001205 - was ->value
}