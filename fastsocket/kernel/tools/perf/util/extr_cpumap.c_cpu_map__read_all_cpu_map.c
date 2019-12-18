#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cpu_map {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct cpu_map* cpu_map__default_new () ; 
 struct cpu_map* cpu_map__read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 

__attribute__((used)) static struct cpu_map *cpu_map__read_all_cpu_map(void)
{
	struct cpu_map *cpus = NULL;
	FILE *onlnf;

	onlnf = fopen("/sys/devices/system/cpu/online", "r");
	if (!onlnf)
		return cpu_map__default_new();

	cpus = cpu_map__read(onlnf);
	fclose(onlnf);
	return cpus;
}