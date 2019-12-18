#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ bg_task; int /*<<< orphan*/  win; } ;
struct TYPE_7__ {int /*<<< orphan*/  text; TYPE_1__ obj; } ;
typedef  TYPE_2__ MY_OBJ ;

/* Variables and functions */
 int MARGIN ; 
 int getmaxx (int /*<<< orphan*/ ) ; 
 int getmaxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_lines (TYPE_2__*,int) ; 
 int /*<<< orphan*/  print_page (TYPE_2__*,int,int) ; 

__attribute__((used)) static void
print_last_page(MY_OBJ * obj)
{
    int high = getmaxy(obj->obj.win) - (2 * MARGIN + (obj->obj.bg_task ? 1 : 3));
    int wide = getmaxx(obj->text);

    last_lines(obj, high);
    print_page(obj, high, wide);
}