#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  text; scalar_t__ end_reached; scalar_t__ page_length; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  dlg_trace_win (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_line (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_page(MY_OBJ * obj, int height, int width)
{
    int i, passed_end = 0;

    obj->page_length = 0;
    for (i = 0; i < height; i++) {
	print_line(obj, i, width);
	if (!passed_end)
	    obj->page_length++;
	if (obj->end_reached && !passed_end)
	    passed_end = 1;
    }
    (void) wnoutrefresh(obj->text);
    dlg_trace_win(obj->text);
}