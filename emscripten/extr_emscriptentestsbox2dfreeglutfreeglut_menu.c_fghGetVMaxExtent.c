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
struct TYPE_4__ {int ScreenWidth; int ScreenHeight; } ;
struct TYPE_3__ {scalar_t__ GameModeWindow; } ;
typedef  int /*<<< orphan*/  SFG_Window ;
typedef  int /*<<< orphan*/  GLvoid ;

/* Variables and functions */
 int /*<<< orphan*/  GLUT_SCREEN_HEIGHT ; 
 int /*<<< orphan*/  GLUT_SCREEN_WIDTH ; 
 TYPE_2__ fgDisplay ; 
 TYPE_1__ fgStructure ; 
 int glutGet (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GLvoid fghGetVMaxExtent( SFG_Window* window, int* x, int* y )
{
    if( fgStructure.GameModeWindow )
    {
#if TARGET_HOST_POSIX_X11
        int wx, wy;
        Window w;

        XTranslateCoordinates(
            fgDisplay.Display,
            window->Window.Handle,
            fgDisplay.RootWindow,
            0, 0, &wx, &wy, &w);

        *x = fgState.GameModeSize.X + wx;
        *y = fgState.GameModeSize.Y + wy;
#else
        *x = glutGet ( GLUT_SCREEN_WIDTH );
        *y = glutGet ( GLUT_SCREEN_HEIGHT );
#endif
    }
    else
    {
        *x = fgDisplay.ScreenWidth;
        *y = fgDisplay.ScreenHeight;
    }
}