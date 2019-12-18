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

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  Log_flushlog () ; 
 int MONITOR_Run () ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDestroyImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeColormap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreePixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSync (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUnmapWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autorepeat_off () ; 
 int /*<<< orphan*/  autorepeat_restore () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  cmap ; 
 int /*<<< orphan*/ * display ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * image ; 
 int /*<<< orphan*/ * image_data ; 
 int js0 ; 
 int js1 ; 
 int /*<<< orphan*/  pixmap ; 
 scalar_t__ private_cmap ; 
 int /*<<< orphan*/  window ; 

int PLATFORM_Exit(int run_monitor)
{
	int restart;

	Log_flushlog();
	if (run_monitor) {
		autorepeat_restore();
		restart = MONITOR_Run();
		autorepeat_off();
	}
	else
		restart = FALSE;

	if (!restart) {
		if (image_data != NULL)
			free(image_data);

		if (display != NULL) {
			XSync(display, True);

			if (private_cmap)
				XFreeColormap(display, cmap);

#ifdef SHM
			if (image != NULL)
				XDestroyImage(image);
#else
			XFreePixmap(display, pixmap);
#endif
			XUnmapWindow(display, window);
			XDestroyWindow(display, window);
			autorepeat_restore();
			XCloseDisplay(display);
		}

#ifdef LINUX_JOYSTICK
		if (js0 != -1)
			close(js0);

		if (js1 != -1)
			close(js1);
#endif

	}
	return restart;
}