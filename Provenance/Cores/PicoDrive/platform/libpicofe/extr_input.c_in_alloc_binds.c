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
struct in_default_bind {int bit; scalar_t__ btype; int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  binds ;
struct TYPE_2__ {struct in_default_bind* defbinds; } ;

/* Variables and functions */
 TYPE_1__ DRV (int) ; 
 int IN_BINDTYPE_COUNT ; 
 size_t IN_BIND_OFFS (int /*<<< orphan*/ ,scalar_t__) ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int *in_alloc_binds(int drv_id, int key_count)
{
	const struct in_default_bind *defbinds;
	int *binds;
	int i;

	binds = calloc(key_count * IN_BINDTYPE_COUNT * 2, sizeof(binds[0]));
	if (binds == NULL)
		return NULL;

	defbinds = DRV(drv_id).defbinds;
	if (defbinds != NULL) {
		for (i = 0; ; i++) {
			if (defbinds[i].bit == 0 && defbinds[i].btype == 0
			    && defbinds[i].bit == 0)
				break;
			binds[IN_BIND_OFFS(defbinds[i].code, defbinds[i].btype)] |=
				1 << defbinds[i].bit;
		}

		/* always have a copy of defbinds */
		memcpy(binds + key_count * IN_BINDTYPE_COUNT, binds,
			sizeof(binds[0]) * key_count * IN_BINDTYPE_COUNT);
	}

	return binds;
}