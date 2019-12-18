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
struct TYPE_2__ {int* KeyBinds; } ;

/* Variables and functions */
 TYPE_1__ currentConfig ; 

__attribute__((used)) static int count_bound_keys(int action, int pl_idx)
{
	int i, keys = 0;

	for (i = 0; i < 32; i++)
	{
		if (pl_idx >= 0 && (currentConfig.KeyBinds[i]&0x30000) != (pl_idx<<16)) continue;
		if (currentConfig.KeyBinds[i] & action) keys++;
	}

	return keys;
}