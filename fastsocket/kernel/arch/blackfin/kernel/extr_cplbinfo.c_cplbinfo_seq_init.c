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
struct cplbinfo_data {char cplb_type; int /*<<< orphan*/  switched; int /*<<< orphan*/  tbl; int /*<<< orphan*/  mem_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfin_read_DMEM_CONTROL () ; 
 int /*<<< orphan*/  bfin_read_IMEM_CONTROL () ; 
 int /*<<< orphan*/ * dcplb_tbl ; 
 int /*<<< orphan*/  first_switched_dcplb ; 
 int /*<<< orphan*/  first_switched_icplb ; 
 int /*<<< orphan*/ * icplb_tbl ; 

__attribute__((used)) static void cplbinfo_seq_init(struct cplbinfo_data *cdata, unsigned int cpu)
{
	if (cdata->cplb_type == 'I') {
		cdata->mem_control = bfin_read_IMEM_CONTROL();
		cdata->tbl = icplb_tbl[cpu];
		cdata->switched = first_switched_icplb;
	} else {
		cdata->mem_control = bfin_read_DMEM_CONTROL();
		cdata->tbl = dcplb_tbl[cpu];
		cdata->switched = first_switched_dcplb;
	}
}