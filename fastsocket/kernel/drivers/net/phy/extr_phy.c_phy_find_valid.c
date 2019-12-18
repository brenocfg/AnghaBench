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
typedef  int u32 ;
struct TYPE_2__ {int setting; } ;

/* Variables and functions */
 int MAX_NUM_SETTINGS ; 
 TYPE_1__* settings ; 

__attribute__((used)) static inline int phy_find_valid(int idx, u32 features)
{
	while (idx < MAX_NUM_SETTINGS && !(settings[idx].setting & features))
		idx++;

	return idx < MAX_NUM_SETTINGS ? idx : MAX_NUM_SETTINGS - 1;
}