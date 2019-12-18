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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DTRACE_QUANTIZE_BUCKETVAL (int) ; 
 int DTRACE_QUANTIZE_NBUCKETS ; 
 int DTRACE_QUANTIZE_ZEROBUCKET ; 
 int /*<<< orphan*/  EDT_DMISMATCH ; 
 scalar_t__ dt_print_quanthdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_print_quantline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__ const,int /*<<< orphan*/ ,long double,char,char) ; 
 scalar_t__ dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,long long) ; 
 int /*<<< orphan*/  dt_quantize_total (int /*<<< orphan*/ *,scalar_t__ const,long double*) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dt_print_quantize(dtrace_hdl_t *dtp, FILE *fp, const void *addr,
    size_t size, uint64_t normal)
{
	const int64_t *data = addr;
	int i, first_bin = 0, last_bin = DTRACE_QUANTIZE_NBUCKETS - 1;
	long double total = 0;
	char positives = 0, negatives = 0;

	if (size != DTRACE_QUANTIZE_NBUCKETS * sizeof (uint64_t))
		return (dt_set_errno(dtp, EDT_DMISMATCH));

	while (first_bin < DTRACE_QUANTIZE_NBUCKETS - 1 && data[first_bin] == 0)
		first_bin++;

	if (first_bin == DTRACE_QUANTIZE_NBUCKETS - 1) {
		/*
		 * There isn't any data.  This is possible if the aggregation
		 * has been clear()'d or if negative increment values have been
		 * used.  Regardless, we'll print the buckets around 0.
		 */
		first_bin = DTRACE_QUANTIZE_ZEROBUCKET - 1;
		last_bin = DTRACE_QUANTIZE_ZEROBUCKET + 1;
	} else {
		if (first_bin > 0)
			first_bin--;

		while (last_bin > 0 && data[last_bin] == 0)
			last_bin--;

		if (last_bin < DTRACE_QUANTIZE_NBUCKETS - 1)
			last_bin++;
	}

	for (i = first_bin; i <= last_bin; i++) {
		positives |= (data[i] > 0);
		negatives |= (data[i] < 0);
		dt_quantize_total(dtp, data[i], &total);
	}

	if (dt_print_quanthdr(dtp, fp, 0) < 0)
		return (-1);

	for (i = first_bin; i <= last_bin; i++) {
		if (dt_printf(dtp, fp, "%16lld ",
		    (long long)DTRACE_QUANTIZE_BUCKETVAL(i)) < 0)
			return (-1);

		if (dt_print_quantline(dtp, fp, data[i], normal, total,
		    positives, negatives) < 0)
			return (-1);
	}

	return (0);
}