#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ t_type; int /*<<< orphan*/ * t_name; struct TYPE_4__* t_next; } ;
typedef  TYPE_1__ tdesc_t ;

/* Variables and functions */
 scalar_t__ ENUM ; 
 scalar_t__ INTRINSIC ; 
 scalar_t__ STRUCT ; 
 scalar_t__ TYPEDEF ; 
 scalar_t__ UNION ; 
 int compute_sum (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static tdesc_t *
lookup_name(tdesc_t **hash, const char *name1)
{
	int bucket = compute_sum(name1);
	tdesc_t *tdp, *ttdp = NULL;

	for (tdp = hash[bucket]; tdp != NULL; tdp = tdp->t_next) {
		if (tdp->t_name != NULL && strcmp(tdp->t_name, name1) == 0) {
			if (tdp->t_type == STRUCT || tdp->t_type == UNION ||
			    tdp->t_type == ENUM || tdp->t_type == INTRINSIC)
				return (tdp);
			if (tdp->t_type == TYPEDEF)
				ttdp = tdp;
		}
	}
	return (ttdp);
}