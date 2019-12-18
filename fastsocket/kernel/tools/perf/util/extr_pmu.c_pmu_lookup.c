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
struct perf_pmu {int /*<<< orphan*/  list; int /*<<< orphan*/  type; int /*<<< orphan*/  name; int /*<<< orphan*/  aliases; int /*<<< orphan*/  format; int /*<<< orphan*/  cpus; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aliases ; 
 int /*<<< orphan*/  format ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pmu_aliases (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmu_cpumask (char*) ; 
 scalar_t__ pmu_format (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ pmu_type (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmus ; 
 int /*<<< orphan*/  strdup (char*) ; 
 struct perf_pmu* zalloc (int) ; 

__attribute__((used)) static struct perf_pmu *pmu_lookup(char *name)
{
	struct perf_pmu *pmu;
	LIST_HEAD(format);
	LIST_HEAD(aliases);
	__u32 type;

	/*
	 * The pmu data we store & need consists of the pmu
	 * type value and format definitions. Load both right
	 * now.
	 */
	if (pmu_format(name, &format))
		return NULL;

	if (pmu_aliases(name, &aliases))
		return NULL;

	if (pmu_type(name, &type))
		return NULL;

	pmu = zalloc(sizeof(*pmu));
	if (!pmu)
		return NULL;

	pmu->cpus = pmu_cpumask(name);

	INIT_LIST_HEAD(&pmu->format);
	INIT_LIST_HEAD(&pmu->aliases);
	list_splice(&format, &pmu->format);
	list_splice(&aliases, &pmu->aliases);
	pmu->name = strdup(name);
	pmu->type = type;
	list_add_tail(&pmu->list, &pmus);
	return pmu;
}