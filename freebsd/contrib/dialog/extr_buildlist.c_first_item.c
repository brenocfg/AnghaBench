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
struct TYPE_3__ {int item_no; int /*<<< orphan*/ * items; int /*<<< orphan*/ * list; } ;
typedef  int /*<<< orphan*/  MY_DATA ;
typedef  TYPE_1__ ALL_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/ * myItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mySide (int) ; 

__attribute__((used)) static int
first_item(ALL_DATA * all, int selected)
{
    MY_DATA *data = all->list + selected;
    int result = -1;
    int n;

    if (myItem(data, 0) != 0) {
	for (n = 0; n < all->item_no; ++n) {
	    if (myItem(data, 0) == &all->items[n]) {
		result = n;
		break;
	    }
	}
    }
    TRACE(("! first_item %s = %d\n", mySide(selected), result));
    return result;
}