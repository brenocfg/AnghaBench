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
struct TYPE_3__ {int item_no; int /*<<< orphan*/ * list; } ;
typedef  int /*<<< orphan*/  MY_DATA ;
typedef  TYPE_1__ ALL_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ myItem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mySide (int) ; 

__attribute__((used)) static int
skip_rows(ALL_DATA * all, int row, int skip, int selected)
{
    MY_DATA *data = all->list + selected;
    int result = row;
    int n;

    if (skip > 0) {
	for (n = row + 1; (n < all->item_no) && (n <= row + skip); ++n) {
	    if (myItem(data, n) == 0)
		break;
	    result = n;
	}
    } else if (skip < 0) {
	result -= skip;
	if (result < 0)
	    result = 0;
    }
    TRACE(("! skip_rows row %d, skip %d, %s = %d\n",
	   row, skip, mySide(selected), result));
    return result;
}