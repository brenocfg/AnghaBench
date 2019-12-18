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
typedef  int /*<<< orphan*/  MyList ;

/* Variables and functions */
 int /*<<< orphan*/  mylist_remove_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mylist_pop_front(MyList *list)
{
   mylist_remove_at(list, 0);
}