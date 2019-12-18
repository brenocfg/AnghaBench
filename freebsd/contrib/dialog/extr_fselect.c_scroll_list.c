#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  win; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int /*<<< orphan*/  beep () ; 
 scalar_t__ change_list (int,TYPE_1__*) ; 
 scalar_t__ data_of (TYPE_1__*) ; 
 int getmaxy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scroll_list(int direction, LIST * list)
{
    if (data_of(list) != 0) {
	int length = getmaxy(list->win);
	if (change_list(direction * length, list))
	    return;
    }
    beep();
}