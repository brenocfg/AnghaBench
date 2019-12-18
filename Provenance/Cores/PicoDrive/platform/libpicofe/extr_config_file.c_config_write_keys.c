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
struct TYPE_4__ {int mask; int /*<<< orphan*/ * name; } ;
struct TYPE_3__ {int mask; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  IN_BINDTYPE_EMU ; 
 int /*<<< orphan*/  IN_BINDTYPE_PLAYER12 ; 
 size_t IN_BIND_OFFS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_CFG_BIND_COUNT ; 
 int IN_MAX_DEVS ; 
 int array_size (int*) ; 
 TYPE_2__* emuctrl_actions ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int* in_adev ; 
 int /*<<< orphan*/  in_get_config (int,int /*<<< orphan*/ ,int*) ; 
 int* in_get_dev_binds (int) ; 
 char* in_get_dev_name (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* in_get_key_name (int,int) ; 
 TYPE_1__* me_ctrl_actions ; 
 char* mystrip (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ *,int) ; 

void config_write_keys(FILE *f)
{
	int d;

	for (d = 0; d < IN_MAX_DEVS; d++)
	{
		const int *binds = in_get_dev_binds(d);
		const char *name = in_get_dev_name(d, 0, 0);
		int k, count = 0;

		if (binds == NULL || name == NULL)
			continue;

		fprintf(f, "binddev = %s\n", name);
		in_get_config(d, IN_CFG_BIND_COUNT, &count);

		for (k = 0; k < count; k++)
		{
			int i, kbinds, mask;
			char act[32];

			act[0] = act[31] = 0;
			name = in_get_key_name(d, k);

			kbinds = binds[IN_BIND_OFFS(k, IN_BINDTYPE_PLAYER12)];
			for (i = 0; kbinds && me_ctrl_actions[i].name != NULL; i++) {
				mask = me_ctrl_actions[i].mask;
				if (mask & kbinds) {
					strncpy(act, me_ctrl_actions[i].name, 31);
					fprintf(f, "bind %s = player1 %s\n", name, mystrip(act));
					kbinds &= ~mask;
				}
				mask = me_ctrl_actions[i].mask << 16;
				if (mask & kbinds) {
					strncpy(act, me_ctrl_actions[i].name, 31);
					fprintf(f, "bind %s = player2 %s\n", name, mystrip(act));
					kbinds &= ~mask;
				}
			}

			kbinds = binds[IN_BIND_OFFS(k, IN_BINDTYPE_EMU)];
			for (i = 0; kbinds && emuctrl_actions[i].name != NULL; i++) {
				mask = emuctrl_actions[i].mask;
				if (mask & kbinds) {
					strncpy(act, emuctrl_actions[i].name, 31);
					fprintf(f, "bind %s = %s\n", name, mystrip(act));
					kbinds &= ~mask;
				}
			}
		}

#ifdef ANALOG_BINDS
		for (k = 0; k < array_size(in_adev); k++)
		{
			if (in_adev[k] == d)
				fprintf(f, "bind_analog = %d\n", k);
		}
#endif
	}
}