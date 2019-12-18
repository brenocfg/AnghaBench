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
typedef  scalar_t__ dtrace_optval_t ;
struct TYPE_3__ {scalar_t__* dt_options; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */
 size_t DTRACEOPT_AGGSORTKEY ; 
 size_t DTRACEOPT_AGGSORTKEYPOS ; 
 size_t DTRACEOPT_AGGSORTREV ; 
 scalar_t__ DTRACEOPT_UNSET ; 
 scalar_t__ INT_MAX ; 
 int dt_aggregate_varkeycmp (void const*,void const*) ; 
 int dt_aggregate_varvalcmp (void const*,void const*) ; 
 int dt_keypos ; 
 int dt_keysort ; 
 int dt_revsort ; 
 int /*<<< orphan*/  qsort (void*,size_t,size_t,int (*) (void const*,void const*)) ; 

void
dt_aggregate_qsort(dtrace_hdl_t *dtp, void *base, size_t nel, size_t width,
    int (*compar)(const void *, const void *))
{
	int rev = dt_revsort, key = dt_keysort, keypos = dt_keypos;
	dtrace_optval_t keyposopt = dtp->dt_options[DTRACEOPT_AGGSORTKEYPOS];

	dt_revsort = (dtp->dt_options[DTRACEOPT_AGGSORTREV] != DTRACEOPT_UNSET);
	dt_keysort = (dtp->dt_options[DTRACEOPT_AGGSORTKEY] != DTRACEOPT_UNSET);

	if (keyposopt != DTRACEOPT_UNSET && keyposopt <= INT_MAX) {
		dt_keypos = (int)keyposopt;
	} else {
		dt_keypos = 0;
	}

	if (compar == NULL) {
		if (!dt_keysort) {
			compar = dt_aggregate_varvalcmp;
		} else {
			compar = dt_aggregate_varkeycmp;
		}
	}

	qsort(base, nel, width, compar);

	dt_revsort = rev;
	dt_keysort = key;
	dt_keypos = keypos;
}