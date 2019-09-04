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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  enum telemetry_pmi { ____Placeholder_telemetry_pmi } telemetry_pmi ;

/* Variables and functions */

int telemetry_pmi_setup(enum telemetry_pmi pmi_ctr, uint64_t period)
{
#if defined(MT_CORE_INSTRS) && defined(MT_CORE_CYCLES)
	static boolean_t sample_all_tasks_aside = FALSE;
	static uint32_t active_tasks_aside = FALSE;
	int error = 0;
	const char *name = "?";

	unsigned int ctr = 0;

	TELEMETRY_PMI_LOCK();

	switch (pmi_ctr) {
	case TELEMETRY_PMI_NONE:
		if (!telemetry_sample_pmis) {
			error = 1;
			goto out;
		}

		telemetry_sample_pmis = FALSE;
		telemetry_sample_all_tasks = sample_all_tasks_aside;
		telemetry_active_tasks = active_tasks_aside;
		error = mt_microstackshot_stop();
		if (!error) {
			printf("telemetry: disabling ustackshot on PMI\n");
		}
		goto out;

	case TELEMETRY_PMI_INSTRS:
		ctr = MT_CORE_INSTRS;
		name = "instructions";
		break;

	case TELEMETRY_PMI_CYCLES:
		ctr = MT_CORE_CYCLES;
		name = "cycles";
		break;

	default:
		error = 1;
		goto out;
	}

	telemetry_sample_pmis = TRUE;
	sample_all_tasks_aside = telemetry_sample_all_tasks;
	active_tasks_aside = telemetry_active_tasks;
	telemetry_sample_all_tasks = FALSE;
	telemetry_active_tasks = 0;

	error = mt_microstackshot_start(ctr, period, telemetry_pmi_handler, NULL);
	if (!error) {
		printf("telemetry: ustackshot every %llu %s\n", period, name);
	}

out:
	TELEMETRY_PMI_UNLOCK();
	return error;
#else /* defined(MT_CORE_INSTRS) && defined(MT_CORE_CYCLES) */
#pragma unused(pmi_ctr, period)
	return 1;
#endif /* !defined(MT_CORE_INSTRS) || !defined(MT_CORE_CYCLES) */
}