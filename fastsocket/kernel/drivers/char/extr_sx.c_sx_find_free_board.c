#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int SX_BOARD_PRESENT ; 
 unsigned int SX_NBOARDS ; 
 TYPE_1__* boards ; 

__attribute__((used)) static unsigned int sx_find_free_board(void)
{
	unsigned int i;

	for (i = 0; i < SX_NBOARDS; i++)
		if (!(boards[i].flags & SX_BOARD_PRESENT))
			break;

	return i;
}