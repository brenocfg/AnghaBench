#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sem_t ;
typedef  int /*<<< orphan*/  XTextProperty ;
struct TYPE_10__ {int /*<<< orphan*/  keycode; } ;
struct TYPE_9__ {unsigned int width; unsigned int height; } ;
struct TYPE_11__ {int type; TYPE_2__ xkey; TYPE_1__ xconfigure; } ;
typedef  TYPE_3__ XEvent ;
typedef  int /*<<< orphan*/  Window ;
struct TYPE_12__ {scalar_t__ class; } ;
typedef  TYPE_4__ Visual ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  BlackPixel (int /*<<< orphan*/ *,int) ; 
#define  ButtonPress 132 
#define  ConfigureNotify 131 
 int DefaultScreen (int /*<<< orphan*/ *) ; 
 TYPE_4__* DefaultVisual (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int DisplayHeight (int /*<<< orphan*/ *,int) ; 
 char* DisplayString (int /*<<< orphan*/ *) ; 
 unsigned int DisplayWidth (int /*<<< orphan*/ *,int) ; 
#define  Expose 130 
 int ExposureMask ; 
#define  KeyPress 129 
 int KeyPressMask ; 
#define  KeyRelease 128 
 int KeyReleaseMask ; 
 int ProtocolRevision (int /*<<< orphan*/ *) ; 
 int ProtocolVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RootWindow (int /*<<< orphan*/ *,int) ; 
 char* ServerVendor (int /*<<< orphan*/ *) ; 
 int StructureNotifyMask ; 
 scalar_t__ TrueColor ; 
 int VendorRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCheckTypedEvent (int /*<<< orphan*/ *,int const,TYPE_3__*) ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCreateSimpleWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* XDisplayName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XInitThreads () ; 
 int /*<<< orphan*/  XMapWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XNextEvent (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XSelectInput (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XSetWMName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XStringListToTextProperty (char**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  key_press_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_release_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*,int,int) ; 
 int scr_changed ; 
 int scr_h ; 
 int scr_w ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  verstring ; 
 int /*<<< orphan*/  ximage_realloc (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/ * xlib_display ; 
 int /*<<< orphan*/  xlib_update () ; 
 int /*<<< orphan*/  xlib_window ; 

__attribute__((used)) static void *xlib_threadf(void *targ)
{
	unsigned int width, height, display_width, display_height;
	sem_t *sem = targ;
	XTextProperty windowName;
	Window win;
	XEvent report;
	Display *display;
	Visual *visual;
	int screen;

	XInitThreads();

	xlib_display = display = XOpenDisplay(NULL);
	if (display == NULL)
	{
		fprintf(stderr, "cannot connect to X server %s\n",
				XDisplayName(NULL));
		sem_post(sem);
		return NULL;
	}

	visual = DefaultVisual(display, 0);
	if (visual->class != TrueColor)
	{
		fprintf(stderr, "cannot handle non true color visual\n");
		XCloseDisplay(display);
		sem_post(sem);
		return NULL;
	}

	printf("X vendor: %s, rel: %d, display: %s, protocol ver: %d.%d\n", ServerVendor(display),
		VendorRelease(display), DisplayString(display), ProtocolVersion(display),
		ProtocolRevision(display));

	screen = DefaultScreen(display);

	ximage_realloc(display, visual);
	sem_post(sem);

	display_width = DisplayWidth(display, screen);
	display_height = DisplayHeight(display, screen);

	xlib_window = win = XCreateSimpleWindow(display,
			RootWindow(display, screen),
			display_width / 2 - scr_w / 2,
			display_height / 2 - scr_h / 2,
			scr_w + 2, scr_h + 2, 1,
			BlackPixel(display, screen),
			BlackPixel(display, screen));

	XStringListToTextProperty((char **)&verstring, 1, &windowName);
	XSetWMName(display, win, &windowName);

	XSelectInput(display, win, ExposureMask |
			KeyPressMask | KeyReleaseMask |
			StructureNotifyMask);

	XMapWindow(display, win);

	while (1)
	{
		XNextEvent(display, &report);
		switch (report.type)
		{
			case Expose:
				while (XCheckTypedEvent(display, Expose, &report))
					;
				xlib_update();
				break;

			case ConfigureNotify:
				width = report.xconfigure.width;
				height = report.xconfigure.height;
				if (scr_w != width - 2 || scr_h != height - 2) {
					scr_w = width - 2;
					scr_h = height - 2;
					scr_changed = 1;
				}
				break;

			case ButtonPress:
				break;

			case KeyPress:
				key_press_event(report.xkey.keycode);
				break;

			case KeyRelease:
				key_release_event(report.xkey.keycode);
				break;

			default:
				break;
		}
	}
}