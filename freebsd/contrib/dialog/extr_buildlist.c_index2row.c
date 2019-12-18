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
struct TYPE_4__ {int item_no; scalar_t__ items; int /*<<< orphan*/ * list; } ;
typedef  int /*<<< orphan*/  MY_DATA ;
typedef  TYPE_1__ ALL_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ myItem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mySide (int) ; 
 scalar_t__ okIndex (TYPE_1__*,int) ; 

__attribute__((used)) static int
index2row(ALL_DATA * all, int choice, int selected)
{
    MY_DATA *data = all->list + selected;
    int result = -1;
    int row;

    if (okIndex(all, choice)) {
	for (row = 0; row < all->item_no; ++row) {
	    TRACE(("!... choice %d: %p vs row %d: %p\n",
		   choice, all->items + choice,
		   row, myItem(data, row)));
	    if (myItem(data, row) == all->items + choice) {
		result = row;
		break;
	    }
	}
    }
    TRACE(("! index2row(choice %d, %s) = %d\n", choice, mySide(selected), result));
    return result;
}