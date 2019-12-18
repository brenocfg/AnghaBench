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
struct TYPE_2__ {int /*<<< orphan*/  blnk_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  Clocky_SS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Clocky_SSval ; 
 int /*<<< orphan*/  END_UPDATE ; 
 int /*<<< orphan*/  FMD_FINISH ; 
 int /*<<< orphan*/  HOST_HEIGHT ; 
 int /*<<< orphan*/  HOST_WIDTH ; 
 int /*<<< orphan*/  Log_flushlog () ; 
 scalar_t__ MONITOR_Run () ; 
 int /*<<< orphan*/  M_ON ; 
 int /*<<< orphan*/  NOVA_SSval ; 
 TYPE_1__* NOVA_xcb ; 
 int /*<<< orphan*/  SetupEmulatedEnvironment () ; 
 int /*<<< orphan*/  ShutdownEmulatedEnvironment () ; 
 int /*<<< orphan*/  appl_exit () ; 
 int /*<<< orphan*/  form_dial (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  graf_mouse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ new_videoram ; 
 int /*<<< orphan*/  wind_update (int /*<<< orphan*/ ) ; 

int PLATFORM_Exit(int run_monitor)
{
	ShutdownEmulatedEnvironment();

#ifdef BUFFERED_LOG
	Log_flushlog();
#endif

	if (run_monitor) {
		if (MONITOR_Run()) {
			SetupEmulatedEnvironment();

			return 1;			/* go back to emulation */
		}
	}

	if (new_videoram)
		free(new_videoram);

	/* unlock GEM */
	wind_update(END_UPDATE);
	form_dial(FMD_FINISH, 0, 0, 0, 0, 0, 0, HOST_WIDTH, HOST_HEIGHT);	/* redraw screen */
	graf_mouse(M_ON, NULL);
	/* GEM exit */
	appl_exit();

#ifdef SCREENSAVER
	Clocky_SS(Clocky_SSval);
	if (NOVA_xcb)
		NOVA_xcb->blnk_time = NOVA_SSval;
#endif

	return 0;
}