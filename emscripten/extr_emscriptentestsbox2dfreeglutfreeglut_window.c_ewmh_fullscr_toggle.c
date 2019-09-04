#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* l; } ;
struct TYPE_12__ {int format; TYPE_3__ data; scalar_t__ message_type; int /*<<< orphan*/  window; } ;
struct TYPE_13__ {TYPE_4__ xclient; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ XEvent ;
struct TYPE_15__ {int StateFullScreen; int /*<<< orphan*/  RootWindow; int /*<<< orphan*/  Display; scalar_t__ State; } ;
struct TYPE_14__ {TYPE_2__* CurrentWindow; } ;
struct TYPE_9__ {int /*<<< orphan*/  Handle; } ;
struct TYPE_10__ {TYPE_1__ Window; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClientMessage ; 
 long SubstructureNotifyMask ; 
 long SubstructureRedirectMask ; 
 int /*<<< orphan*/  XSendEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,TYPE_5__*) ; 
 int _NET_WM_STATE_TOGGLE ; 
 TYPE_7__ fgDisplay ; 
 TYPE_6__ fgStructure ; 

__attribute__((used)) static int ewmh_fullscr_toggle(void)
{
    XEvent xev;
    long evmask = SubstructureRedirectMask | SubstructureNotifyMask;

    if(!fgDisplay.State || !fgDisplay.StateFullScreen) {
        return -1;
    }

    xev.type = ClientMessage;
    xev.xclient.window = fgStructure.CurrentWindow->Window.Handle;
    xev.xclient.message_type = fgDisplay.State;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = _NET_WM_STATE_TOGGLE;
    xev.xclient.data.l[1] = fgDisplay.StateFullScreen;
    xev.xclient.data.l[2] = 0;	/* no second property to toggle */
    xev.xclient.data.l[3] = 1;	/* source indication: application */
    xev.xclient.data.l[4] = 0;	/* unused */

    if(!XSendEvent(fgDisplay.Display, fgDisplay.RootWindow, 0, evmask, &xev)) {
        return -1;
    }
    return 0;
}