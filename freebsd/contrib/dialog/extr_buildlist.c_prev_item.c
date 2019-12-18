#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ALL_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int index2row (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mySide (int) ; 
 int row2index (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
prev_item(ALL_DATA * all, int choice, int selected)
{
    int result = choice;
    int row = index2row(all, choice, selected);
    if (row > 0) {
	row--;
	result = row2index(all, row, selected);
    }
    TRACE(("! prev_item choice %d, %s = %d\n", choice, mySide(selected), result));
    return result;
}