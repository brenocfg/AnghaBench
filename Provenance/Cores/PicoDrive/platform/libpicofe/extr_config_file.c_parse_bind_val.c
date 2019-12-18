#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* name; int mask; } ;
struct TYPE_3__ {char const* name; int mask; } ;

/* Variables and functions */
 int IN_BINDTYPE_EMU ; 
 int IN_BINDTYPE_NONE ; 
 int IN_BINDTYPE_PLAYER12 ; 
 int atoi (char const*) ; 
 TYPE_2__* emuctrl_actions ; 
 TYPE_1__* me_ctrl_actions ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,int) ; 

__attribute__((used)) static int parse_bind_val(const char *val, int *type)
{
	int i;

	*type = IN_BINDTYPE_NONE;
	if (val[0] == 0)
		return 0;
	
	if (strncasecmp(val, "player", 6) == 0)
	{
		int player, shift = 0;
		player = atoi(val + 6) - 1;

		if ((unsigned int)player > 1)
			return -1;
		if (player == 1)
			shift = 16;

		*type = IN_BINDTYPE_PLAYER12;
		for (i = 0; me_ctrl_actions[i].name != NULL; i++) {
			if (strncasecmp(me_ctrl_actions[i].name, val + 8, strlen(val + 8)) == 0)
				return me_ctrl_actions[i].mask << shift;
		}
	}
	for (i = 0; emuctrl_actions[i].name != NULL; i++) {
		if (strncasecmp(emuctrl_actions[i].name, val, strlen(val)) == 0) {
			*type = IN_BINDTYPE_EMU;
			return emuctrl_actions[i].mask;
		}
	}

	return -1;
}