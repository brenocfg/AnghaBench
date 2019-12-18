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
 int /*<<< orphan*/  MEMORY_Cart809fEnable () ; 
 int /*<<< orphan*/  update_8000_9fff () ; 
 int /*<<< orphan*/  update_d5 () ; 

void AF80_InsertRightCartridge(void)
{
		MEMORY_Cart809fEnable();
		update_d5();
		update_8000_9fff();
}