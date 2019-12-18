#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  win; int /*<<< orphan*/ * input; } ;
struct TYPE_6__ {TYPE_1__ obj; int /*<<< orphan*/  last_pos; int /*<<< orphan*/  hscroll; int /*<<< orphan*/  old_hscroll; } ;
typedef  TYPE_2__ MY_OBJ ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  print_last_page (TYPE_2__*) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
repaint_text(MY_OBJ * obj)
{
    FILE *fp = obj->obj.input;
    int cur_y, cur_x;

    getyx(obj->obj.win, cur_y, cur_x);
    obj->old_hscroll = obj->hscroll;

    print_last_page(obj);
    obj->last_pos = ftell(fp);

    (void) wmove(obj->obj.win, cur_y, cur_x);	/* Restore cursor position */
    wrefresh(obj->obj.win);
}