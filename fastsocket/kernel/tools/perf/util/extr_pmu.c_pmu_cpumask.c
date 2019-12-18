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
struct stat {int dummy; } ;
struct cpu_map {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 struct cpu_map* cpu_map__read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* sysfs_find_mountpoint () ; 

__attribute__((used)) static struct cpu_map *pmu_cpumask(char *name)
{
	struct stat st;
	char path[PATH_MAX];
	const char *sysfs;
	FILE *file;
	struct cpu_map *cpus;

	sysfs = sysfs_find_mountpoint();
	if (!sysfs)
		return NULL;

	snprintf(path, PATH_MAX,
		 "%s/bus/event_source/devices/%s/cpumask", sysfs, name);

	if (stat(path, &st) < 0)
		return NULL;

	file = fopen(path, "r");
	if (!file)
		return NULL;

	cpus = cpu_map__read(file);
	fclose(file);
	return cpus;
}