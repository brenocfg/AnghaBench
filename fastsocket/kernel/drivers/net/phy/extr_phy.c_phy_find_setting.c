#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int speed; int duplex; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int MAX_NUM_SETTINGS ; 
 TYPE_1__* settings ; 

__attribute__((used)) static inline int phy_find_setting(int speed, int duplex)
{
	int idx = 0;

	while (idx < ARRAY_SIZE(settings) &&
			(settings[idx].speed != speed ||
			settings[idx].duplex != duplex))
		idx++;

	return idx < MAX_NUM_SETTINGS ? idx : MAX_NUM_SETTINGS - 1;
}