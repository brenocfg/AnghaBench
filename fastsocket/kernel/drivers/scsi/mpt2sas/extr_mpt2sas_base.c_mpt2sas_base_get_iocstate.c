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
typedef  int u32 ;
struct MPT2SAS_ADAPTER {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  Doorbell; } ;

/* Variables and functions */
 int MPI2_IOC_STATE_MASK ; 
 int readl (int /*<<< orphan*/ *) ; 

u32
mpt2sas_base_get_iocstate(struct MPT2SAS_ADAPTER *ioc, int cooked)
{
	u32 s, sc;

	s = readl(&ioc->chip->Doorbell);
	sc = s & MPI2_IOC_STATE_MASK;
	return cooked ? sc : s;
}