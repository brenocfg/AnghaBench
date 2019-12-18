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
 char** keyNames ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *action_binds(int player_idx, int action_mask)
{
	static char strkeys[32*5];
	int i;

	strkeys[0] = 0;
	for (i = 0; i < 32; i++) // i is key index
	{
		if (currentConfig.KeyBinds[i] & action_mask)
		{
			if (player_idx >= 0 && ((currentConfig.KeyBinds[i] >> 16) & 3) != player_idx) continue;
			if (strkeys[0]) { strcat(strkeys, " + "); strcat(strkeys, keyNames[i]); break; }
			else strcpy(strkeys, keyNames[i]);
		}
	}

	return strkeys;
}