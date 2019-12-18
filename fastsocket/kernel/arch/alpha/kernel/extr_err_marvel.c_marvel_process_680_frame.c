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
struct ev7_lf_subpackets {scalar_t__* env; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE ; 
 int /*<<< orphan*/  EL_TYPE__PAL__ENV__HOT_PLUG ; 
 int MCHK_DISPOSITION_REPORT ; 
 int MCHK_DISPOSITION_UNKNOWN_ERROR ; 
 int ev7_lf_env_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marvel_print_680_frame (struct ev7_lf_subpackets*) ; 

__attribute__((used)) static int
marvel_process_680_frame(struct ev7_lf_subpackets *lf_subpackets, int print)
{
	int status = MCHK_DISPOSITION_UNKNOWN_ERROR;
	int i;

	for (i = ev7_lf_env_index(EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE);
	     i <= ev7_lf_env_index(EL_TYPE__PAL__ENV__HOT_PLUG);
	     i++) {
		if (lf_subpackets->env[i])
			status = MCHK_DISPOSITION_REPORT;
	}

	if (print)
		marvel_print_680_frame(lf_subpackets);

	return status;
}