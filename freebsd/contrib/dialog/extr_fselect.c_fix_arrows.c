#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ win; scalar_t__ mousex; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_NEXT ; 
 int /*<<< orphan*/  KEY_NPAGE ; 
 int /*<<< orphan*/  KEY_PPAGE ; 
 int /*<<< orphan*/  KEY_PREVIOUS ; 
 scalar_t__ MOUSE_D ; 
 int getmaxx (scalar_t__) ; 
 int getmaxy (scalar_t__) ; 
 int /*<<< orphan*/  getparyx (scalar_t__,int,int) ; 
 int /*<<< orphan*/  mouse_mkbutton (int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fix_arrows(LIST * list)
{
    int x;
    int y;
    int top;
    int right;
    int bottom;

    if (list->win != 0) {
	getparyx(list->win, y, x);
	top = y - 1;
	right = getmaxx(list->win);
	bottom = y + getmaxy(list->win);

	mouse_mkbutton(top, x, right,
		       ((list->mousex == MOUSE_D)
			? KEY_PREVIOUS
			: KEY_PPAGE));
	mouse_mkbutton(bottom, x, right,
		       ((list->mousex == MOUSE_D)
			? KEY_NEXT
			: KEY_NPAGE));
    }
}