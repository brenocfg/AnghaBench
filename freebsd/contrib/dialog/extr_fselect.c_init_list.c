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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_3__ {int mousex; scalar_t__ data; scalar_t__ allocd; scalar_t__ choice; scalar_t__ offset; scalar_t__ length; int /*<<< orphan*/ * win; int /*<<< orphan*/ * par; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int /*<<< orphan*/  dlg_mouse_mkbigregion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  getbegx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getbegy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getmaxx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getmaxy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
init_list(LIST * list, WINDOW *par, WINDOW *win, int mousex)
{
    list->par = par;
    list->win = win;
    list->length = 0;
    list->offset = 0;
    list->choice = 0;
    list->mousex = mousex;
    list->allocd = 0;
    list->data = 0;
    dlg_mouse_mkbigregion(getbegy(win), getbegx(win),
			  getmaxy(win), getmaxx(win),
			  mousex, 1, 1, 1 /* by lines */ );
}