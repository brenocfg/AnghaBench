#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int item_no; TYPE_1__* items; } ;
struct TYPE_4__ {scalar_t__ state; } ;
typedef  TYPE_2__ ALL_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  mySide (int) ; 

__attribute__((used)) static int
closest_item(ALL_DATA * all, int choice, int selected)
{
    int prev = choice;
    int next = choice;
    int result = choice;
    int n;

    for (n = choice; n >= 0; --n) {
	if ((all->items[n].state != 0) == selected) {
	    prev = n;
	    break;
	}
    }
    for (n = choice; n < all->item_no; ++n) {
	if ((all->items[n].state != 0) == selected) {
	    next = n;
	    break;
	}
    }
    if (prev != choice) {
	result = prev;
	if (next != choice) {
	    if ((choice - prev) > (next - choice)) {
		result = next;
	    }
	}
    } else if (next != choice) {
	result = next;
    }
    TRACE(("! XXX closest item choice %d, %s = %d\n",
	   choice, mySide(selected), result));
    return result;
}