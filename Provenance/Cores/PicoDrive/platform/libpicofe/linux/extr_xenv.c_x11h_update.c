#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int x; int y; } ;
struct TYPE_7__ {int x; int y; int button; } ;
struct TYPE_9__ {int type; TYPE_2__ xmotion; TYPE_1__ xbutton; int /*<<< orphan*/  xkey; } ;
typedef  TYPE_3__ XEvent ;
struct TYPE_10__ {int (* pXLookupKeysym ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  display; int /*<<< orphan*/  (* pXCheckTypedEvent ) (int /*<<< orphan*/ ,int const,TYPE_3__*) ;int /*<<< orphan*/  (* pXNextEvent ) (int /*<<< orphan*/ ,TYPE_3__*) ;scalar_t__ (* pXPending ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  ButtonPress 133 
#define  ButtonRelease 132 
#define  Expose 131 
#define  KeyPress 130 
#define  KeyRelease 129 
#define  MotionNotify 128 
 TYPE_6__ g_xstuff ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int const,TYPE_3__*) ; 
 int stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void x11h_update(int (*key_cb)(void *cb_arg, int kc, int is_pressed),
			int (*mouseb_cb)(void *cb_arg, int x, int y, int button, int is_pressed),
			int (*mousem_cb)(void *cb_arg, int x, int y),
			void *cb_arg)
{
	XEvent evt;
	int keysym;

	while (g_xstuff.pXPending(g_xstuff.display))
	{
		g_xstuff.pXNextEvent(g_xstuff.display, &evt);
		switch (evt.type)
		{
		case Expose:
			while (g_xstuff.pXCheckTypedEvent(g_xstuff.display, Expose, &evt))
				;
			break;

		case KeyPress:
			keysym = g_xstuff.pXLookupKeysym(&evt.xkey, 0);
			if (key_cb != NULL)
				key_cb(cb_arg, keysym, 1);
			break;

		case KeyRelease:
			keysym = g_xstuff.pXLookupKeysym(&evt.xkey, 0);
			if (key_cb != NULL)
				key_cb(cb_arg, keysym, 0);
			break;

		case ButtonPress:
			if (mouseb_cb != NULL)
				mouseb_cb(cb_arg, evt.xbutton.x, evt.xbutton.y,
					  evt.xbutton.button, 1);
			break;

		case ButtonRelease:
			if (mouseb_cb != NULL)
				mouseb_cb(cb_arg, evt.xbutton.x, evt.xbutton.y,
					  evt.xbutton.button, 0);
			break;

		case MotionNotify:
			if (mousem_cb != NULL)
				mousem_cb(cb_arg, evt.xmotion.x, evt.xmotion.y);
			break;
		}
	}
}