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
struct TYPE_3__ {size_t code; int /*<<< orphan*/  hz; } ;
typedef  TYPE_1__ hz_init_t ;
typedef  int /*<<< orphan*/  hazard_t ;

/* Variables and functions */
 int /*<<< orphan*/  forbidden_command ; 

__attribute__((used)) static void
setup_hazard_table(hz_init_t init_table[], hazard_t table[], int size)
{
	int i;

	for (i = 0; i < 256; ++i)
		table[i] = forbidden_command;

	for (i = 0; i < size; ++i)
		table[init_table[i].code] = init_table[i].hz;
}