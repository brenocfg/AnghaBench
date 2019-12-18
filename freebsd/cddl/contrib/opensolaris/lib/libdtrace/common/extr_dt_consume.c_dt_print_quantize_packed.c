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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_3__ {int dtada_minbin; int dtada_maxbin; } ;
typedef  TYPE_1__ dtrace_aggdata_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DTRACE_QUANTIZE_BUCKETVAL (int) ; 
 int DTRACE_QUANTIZE_NBUCKETS ; 
 int DTRACE_QUANTIZE_ZEROBUCKET ; 
 int /*<<< orphan*/  EDT_DMISMATCH ; 
 int /*<<< orphan*/  dt_ndigits (scalar_t__) ; 
 scalar_t__ dt_print_packed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__ const,long double) ; 
 scalar_t__ dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,long long,...) ; 
 int /*<<< orphan*/  dt_quantize_total (int /*<<< orphan*/ *,scalar_t__ const,long double*) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dt_print_quantize_packed(dtrace_hdl_t *dtp, FILE *fp, const void *addr,
    size_t size, const dtrace_aggdata_t *aggdata)
{
	const int64_t *data = addr;
	long double total = 0, count = 0;
	int min = aggdata->dtada_minbin, max = aggdata->dtada_maxbin, i;
	int64_t minval, maxval;

	if (size != DTRACE_QUANTIZE_NBUCKETS * sizeof (uint64_t))
		return (dt_set_errno(dtp, EDT_DMISMATCH));

	if (min != 0 && min != DTRACE_QUANTIZE_ZEROBUCKET)
		min--;

	if (max < DTRACE_QUANTIZE_NBUCKETS - 1)
		max++;

	minval = DTRACE_QUANTIZE_BUCKETVAL(min);
	maxval = DTRACE_QUANTIZE_BUCKETVAL(max);

	if (dt_printf(dtp, fp, " %*lld :", dt_ndigits(minval),
	    (long long)minval) < 0)
		return (-1);

	for (i = min; i <= max; i++) {
		dt_quantize_total(dtp, data[i], &total);
		count += data[i];
	}

	for (i = min; i <= max; i++) {
		if (dt_print_packed(dtp, fp, data[i], total) < 0)
			return (-1);
	}

	if (dt_printf(dtp, fp, ": %*lld | %lld\n",
	    -dt_ndigits(maxval), (long long)maxval, (long long)count) < 0)
		return (-1);

	return (0);
}