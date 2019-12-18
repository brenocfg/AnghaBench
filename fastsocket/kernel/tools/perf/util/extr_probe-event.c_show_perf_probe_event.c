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
struct perf_probe_event {int nargs; int /*<<< orphan*/ * args; int /*<<< orphan*/  event; int /*<<< orphan*/  group; int /*<<< orphan*/  point; } ;

/* Variables and functions */
 int EINVAL ; 
 int e_snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int synthesize_perf_probe_arg (int /*<<< orphan*/ *,char*,int) ; 
 char* synthesize_perf_probe_point (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int show_perf_probe_event(struct perf_probe_event *pev)
{
	int i, ret;
	char buf[128];
	char *place;

	/* Synthesize only event probe point */
	place = synthesize_perf_probe_point(&pev->point);
	if (!place)
		return -EINVAL;

	ret = e_snprintf(buf, 128, "%s:%s", pev->group, pev->event);
	if (ret < 0)
		return ret;

	printf("  %-20s (on %s", buf, place);

	if (pev->nargs > 0) {
		printf(" with");
		for (i = 0; i < pev->nargs; i++) {
			ret = synthesize_perf_probe_arg(&pev->args[i],
							buf, 128);
			if (ret < 0)
				break;
			printf(" %s", buf);
		}
	}
	printf(")\n");
	free(place);
	return ret;
}