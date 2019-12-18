#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * qs; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int SGE_QSETS ; 
 int /*<<< orphan*/  t3_free_qset (struct adapter*,int /*<<< orphan*/ *) ; 

void t3_free_sge_resources(struct adapter *adap)
{
	int i;

	for (i = 0; i < SGE_QSETS; ++i)
		t3_free_qset(adap, &adap->sge.qs[i]);
}