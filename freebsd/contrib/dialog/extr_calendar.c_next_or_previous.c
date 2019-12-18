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
#define  DLGK_GRID_DOWN 131 
#define  DLGK_GRID_LEFT 130 
#define  DLGK_GRID_RIGHT 129 
#define  DLGK_GRID_UP 128 
 int MAX_DAYS ; 
 int /*<<< orphan*/  beep () ; 

__attribute__((used)) static int
next_or_previous(int key, int two_d)
{
    int result = 0;

    switch (key) {
    case DLGK_GRID_UP:
	result = two_d ? -MAX_DAYS : -1;
	break;
    case DLGK_GRID_LEFT:
	result = -1;
	break;
    case DLGK_GRID_DOWN:
	result = two_d ? MAX_DAYS : 1;
	break;
    case DLGK_GRID_RIGHT:
	result = 1;
	break;
    default:
	beep();
	break;
    }
    return result;
}