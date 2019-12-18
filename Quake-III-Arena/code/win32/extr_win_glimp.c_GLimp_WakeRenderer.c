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
struct TYPE_2__ {int /*<<< orphan*/  hDC; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ glw_state ; 
 int /*<<< orphan*/  qwglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  renderActiveEvent ; 
 int /*<<< orphan*/  renderCommandsEvent ; 
 void* smpData ; 
 int /*<<< orphan*/  wglErrors ; 

void GLimp_WakeRenderer( void *data ) {
	smpData = data;

	if ( !qwglMakeCurrent( glw_state.hDC, NULL ) ) {
		wglErrors++;
	}

	// after this, the renderer can continue through GLimp_RendererSleep
	SetEvent( renderCommandsEvent );

	WaitForSingleObject( renderActiveEvent, INFINITE );
}