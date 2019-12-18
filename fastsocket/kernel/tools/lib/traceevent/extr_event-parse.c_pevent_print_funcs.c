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
struct pevent {TYPE_1__* func_map; scalar_t__ func_count; } ;
struct TYPE_2__ {char* mod; int /*<<< orphan*/  func; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  func_map_init (struct pevent*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void pevent_print_funcs(struct pevent *pevent)
{
	int i;

	if (!pevent->func_map)
		func_map_init(pevent);

	for (i = 0; i < (int)pevent->func_count; i++) {
		printf("%016llx %s",
		       pevent->func_map[i].addr,
		       pevent->func_map[i].func);
		if (pevent->func_map[i].mod)
			printf(" [%s]\n", pevent->func_map[i].mod);
		else
			printf("\n");
	}
}