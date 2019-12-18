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
typedef  int uint16_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DTRACE_LLQUANTIZE_FACTOR (int /*<<< orphan*/ ) ; 
 int DTRACE_LLQUANTIZE_HIGH (int /*<<< orphan*/ ) ; 
 int DTRACE_LLQUANTIZE_LOW (int /*<<< orphan*/ ) ; 
 int DTRACE_LLQUANTIZE_NSTEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDT_DMISMATCH ; 
 size_t INT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int dt_print_quantline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__ const,int /*<<< orphan*/ ,long double,char,char) ; 
 scalar_t__ dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dt_quantize_total (int /*<<< orphan*/ *,scalar_t__ const,long double*) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long long) ; 

int
dt_print_llquantize(dtrace_hdl_t *dtp, FILE *fp, const void *addr,
    size_t size, uint64_t normal)
{
	int i, first_bin, last_bin, bin = 1, order, levels;
	uint16_t factor, low, high, nsteps;
	const int64_t *data = addr;
	int64_t value = 1, next, step;
	char positives = 0, negatives = 0;
	long double total = 0;
	uint64_t arg;
	char c[32];

	if (size < sizeof (uint64_t))
		return (dt_set_errno(dtp, EDT_DMISMATCH));

	arg = *data++;
	size -= sizeof (uint64_t);

	factor = DTRACE_LLQUANTIZE_FACTOR(arg);
	low = DTRACE_LLQUANTIZE_LOW(arg);
	high = DTRACE_LLQUANTIZE_HIGH(arg);
	nsteps = DTRACE_LLQUANTIZE_NSTEP(arg);

	/*
	 * We don't expect to be handed invalid llquantize() parameters here,
	 * but sanity check them (to a degree) nonetheless.
	 */
	if (size > INT32_MAX || factor < 2 || low >= high ||
	    nsteps == 0 || factor > nsteps)
		return (dt_set_errno(dtp, EDT_DMISMATCH));

	levels = (int)size / sizeof (uint64_t);

	first_bin = 0;
	last_bin = levels - 1;

	while (first_bin < levels && data[first_bin] == 0)
		first_bin++;

	if (first_bin == levels) {
		first_bin = 0;
		last_bin = 1;
	} else {
		if (first_bin > 0)
			first_bin--;

		while (last_bin > 0 && data[last_bin] == 0)
			last_bin--;

		if (last_bin < levels - 1)
			last_bin++;
	}

	for (i = first_bin; i <= last_bin; i++) {
		positives |= (data[i] > 0);
		negatives |= (data[i] < 0);
		dt_quantize_total(dtp, data[i], &total);
	}

	if (dt_printf(dtp, fp, "\n%16s %41s %-9s\n", "value",
	    "------------- Distribution -------------", "count") < 0)
		return (-1);

	for (order = 0; order < low; order++)
		value *= factor;

	next = value * factor;
	step = next > nsteps ? next / nsteps : 1;

	if (first_bin == 0) {
		(void) snprintf(c, sizeof (c), "< %lld", (long long)value);

		if (dt_printf(dtp, fp, "%16s ", c) < 0)
			return (-1);

		if (dt_print_quantline(dtp, fp, data[0], normal,
		    total, positives, negatives) < 0)
			return (-1);
	}

	while (order <= high) {
		if (bin >= first_bin && bin <= last_bin) {
			if (dt_printf(dtp, fp, "%16lld ", (long long)value) < 0)
				return (-1);

			if (dt_print_quantline(dtp, fp, data[bin],
			    normal, total, positives, negatives) < 0)
				return (-1);
		}

		assert(value < next);
		bin++;

		if ((value += step) != next)
			continue;

		next = value * factor;
		step = next > nsteps ? next / nsteps : 1;
		order++;
	}

	if (last_bin < bin)
		return (0);

	assert(last_bin == bin);
	(void) snprintf(c, sizeof (c), ">= %lld", (long long)value);

	if (dt_printf(dtp, fp, "%16s ", c) < 0)
		return (-1);

	return (dt_print_quantline(dtp, fp, data[bin], normal,
	    total, positives, negatives));
}