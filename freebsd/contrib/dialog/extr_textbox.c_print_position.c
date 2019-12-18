#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_8__ {scalar_t__ tab_correct; } ;
struct TYPE_7__ {long in_buf; long fd_bytes_read; int /*<<< orphan*/  file_size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */
 scalar_t__ PAGE_LENGTH ; 
 int /*<<< orphan*/  PAGE_WIDTH ; 
 int /*<<< orphan*/  border_attr ; 
 TYPE_6__ dialog_vars ; 
 int /*<<< orphan*/  dlg_draw_scrollbar (int /*<<< orphan*/ *,long,long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long find_first (TYPE_1__*,int /*<<< orphan*/ ,long) ; 
 long ftell_obj (TYPE_1__*) ; 
 long tabize (TYPE_1__*,long,long*) ; 

__attribute__((used)) static void
print_position(MY_OBJ * obj, WINDOW *win, int height, int width)
{
    long fpos;
    long size;
    long first = -1;

    fpos = ftell_obj(obj);
    if (dialog_vars.tab_correct)
	size = tabize(obj, obj->in_buf, &first);
    else
	first = find_first(obj, obj->buf, size = obj->in_buf);

    dlg_draw_scrollbar(win,
		       first,
		       fpos - obj->fd_bytes_read + size,
		       fpos - obj->fd_bytes_read + size,
		       obj->file_size,
		       0, PAGE_WIDTH,
		       0, PAGE_LENGTH + 1,
		       border_attr,
		       border_attr);
}