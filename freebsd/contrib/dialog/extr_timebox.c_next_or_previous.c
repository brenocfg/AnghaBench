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

/* Variables and functions */
#define  DLGK_ITEM_NEXT 129 
#define  DLGK_ITEM_PREV 128 
 int /*<<< orphan*/  beep () ; 

__attribute__((used)) static int
next_or_previous(int key)
{
    int result = 0;

    switch (key) {
    case DLGK_ITEM_PREV:
	result = -1;
	break;
    case DLGK_ITEM_NEXT:
	result = 1;
	break;
    default:
	beep();
	break;
    }
    return result;
}