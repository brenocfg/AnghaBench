#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ XWindowAttributes ;
struct TYPE_13__ {int /*<<< orphan*/  ScreenHeight; int /*<<< orphan*/  ScreenWidth; int /*<<< orphan*/  Display; } ;
struct TYPE_12__ {TYPE_4__* CurrentWindow; } ;
struct TYPE_9__ {int /*<<< orphan*/  Handle; } ;
struct TYPE_8__ {int /*<<< orphan*/  OldHeight; int /*<<< orphan*/  Height; int /*<<< orphan*/  OldWidth; int /*<<< orphan*/  Width; int /*<<< orphan*/  NeedToResize; } ;
struct TYPE_11__ {TYPE_2__ Window; TYPE_1__ State; } ;
typedef  TYPE_4__ SFG_Window ;

/* Variables and functions */
 int /*<<< orphan*/  GLUT_FULL_SCREEN ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  XMoveResizeWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ fgDisplay ; 
 TYPE_5__ fgStructure ; 
 scalar_t__ glutGet (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resize_fullscr_toogle(void)
{
    XWindowAttributes attributes;

    if(glutGet(GLUT_FULL_SCREEN)) {
        /* restore original window size */
        SFG_Window *win = fgStructure.CurrentWindow;
        fgStructure.CurrentWindow->State.NeedToResize = GL_TRUE;
        fgStructure.CurrentWindow->State.Width  = win->State.OldWidth;
        fgStructure.CurrentWindow->State.Height = win->State.OldHeight;

    } else {
        /* resize the window to cover the entire screen */
        XGetWindowAttributes(fgDisplay.Display,
                fgStructure.CurrentWindow->Window.Handle,
                &attributes);
        
        /*
         * The "x" and "y" members of "attributes" are the window's coordinates
         * relative to its parent, i.e. to the decoration window.
         */
        XMoveResizeWindow(fgDisplay.Display,
                fgStructure.CurrentWindow->Window.Handle,
                -attributes.x,
                -attributes.y,
                fgDisplay.ScreenWidth,
                fgDisplay.ScreenHeight);
    }
    return 0;
}