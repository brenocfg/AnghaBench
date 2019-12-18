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
 int /*<<< orphan*/  PokeMini_KeypadEvent (int,int) ; 

void UIMenu_KeyEvent(int key, int press) {
	if (press) {
		PokeMini_KeypadEvent(key, 1);
	} else {
		PokeMini_KeypadEvent(key, 0);
	}
}