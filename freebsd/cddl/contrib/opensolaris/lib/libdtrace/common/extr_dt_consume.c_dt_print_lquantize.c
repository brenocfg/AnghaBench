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
 int DTRACE_LQUANTIZE_BASE (int /*<<< orphan*/ ) ; 
 int DTRACE_LQUANTIZE_LEVELS (int /*<<< orphan*/ ) ; 
 int DTRACE_LQUANTIZE_STEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDT_DMISMATCH ; 
 scalar_t__ dt_print_quantline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__ const,int /*<<< orphan*/ ,long double,char,char) ; 
 int dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dt_quantize_total (int /*<<< orphan*/ *,scalar_t__ const,long double*) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int
dt_print_lquantize(dtrace_hdl_t *dtp, FILE *fp, const void *addr,
    size_t size, uint64_t normal)
{
	const int64_t *data = addr;
	int i, first_bin, last_bin, base;
	uint64_t arg;
	long double total = 0;
	uint16_t step, levels;
	char positives = 0, negatives = 0;

	if (size < sizeof (uint64_t))
		return (dt_set_errno(dtp, EDT_DMISMATCH));

	arg = *data++;
	size -= sizeof (uint64_t);

	base = DTRACE_LQUANTIZE_BASE(arg);
	step = DTRACE_LQUANTIZE_STEP(arg);
	levels = DTRACE_LQUANTIZE_LEVELS(arg);

	first_bin = 0;
	last_bin = levels + 1;

	if (size != sizeof (uint64_t) * (levels + 2))
		return (dt_set_errno(dtp, EDT_DMISMATCH));

	while (first_bin <= levels + 1 && data[first_bin] == 0)
		first_bin++;

	if (first_bin > levels + 1) {
		first_bin = 0;
		last_bin = 2;
	} else {
		if (first_bin > 0)
			first_bin--;

		while (last_bin > 0 && data[last_bin] == 0)
			last_bin--;

		if (last_bin < levels + 1)
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

	for (i = first_bin; i <= last_bin; i++) {
		char c[32];
		int err;

		if (i == 0) {
			(void) snprintf(c, sizeof (c), "< %d", base);
			err = dt_printf(dtp, fp, "%16s ", c);
		} else if (i == levels + 1) {
			(void) snprintf(c, sizeof (c), ">= %d",
			    base + (levels * step));
			err = dt_printf(dtp, fp, "%16s ", c);
		} else {
			err = dt_printf(dtp, fp, "%16d ",
			    base + (i - 1) * step);
		}

		if (err < 0 || dt_print_quantline(dtp, fp, data[i], normal,
		    total, positives, negatives) < 0)
			return (-1);
	}

	return (0);
}