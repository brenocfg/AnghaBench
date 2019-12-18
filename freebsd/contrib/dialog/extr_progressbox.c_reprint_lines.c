#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */
 int getmaxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_line (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrote_data (TYPE_1__*,int) ; 
 int wrote_size (TYPE_1__*,int) ; 

__attribute__((used)) static int
reprint_lines(MY_OBJ * obj, int buttons)
{
    int want = getmaxy(obj->text) - (buttons ? 2 : 0);
    int have = wrote_size(obj, want);
    int n;
    for (n = 0; n < have; ++n) {
	print_line(obj, wrote_data(obj, have - n), n);
    }
    (void) wrefresh(obj->text);
    return have;
}