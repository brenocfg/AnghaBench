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
struct TYPE_2__ {int ModeIndex; } ;

/* Variables and functions */
 TYPE_1__* CLE266Modes ; 
 int NUM_TOTAL_MODETABLE ; 

__attribute__((used)) static int search_mode_setting(int ModeInfoIndex)
{
	int i = 0;

	while ((i < NUM_TOTAL_MODETABLE) &&
			(ModeInfoIndex != CLE266Modes[i].ModeIndex))
		i++;
	if (i >= NUM_TOTAL_MODETABLE)
		i = 0;
	return i;

}