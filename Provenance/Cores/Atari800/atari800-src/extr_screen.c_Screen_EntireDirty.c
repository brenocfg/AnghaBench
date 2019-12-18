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
 int Screen_HEIGHT ; 
 int Screen_WIDTH ; 
 scalar_t__ Screen_dirty ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 

void Screen_EntireDirty(void)
{
#ifdef DIRTYRECT
	if (Screen_dirty)
		memset(Screen_dirty, 1, Screen_WIDTH * Screen_HEIGHT / 8);
#endif /* DIRTYRECT */
}