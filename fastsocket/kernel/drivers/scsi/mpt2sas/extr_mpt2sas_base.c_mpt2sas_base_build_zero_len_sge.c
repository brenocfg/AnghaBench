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
typedef  int /*<<< orphan*/  u32 ;
struct MPT2SAS_ADAPTER {int /*<<< orphan*/  (* base_add_sg_single ) (void*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int MPI2_SGE_FLAGS_END_OF_BUFFER ; 
 int MPI2_SGE_FLAGS_END_OF_LIST ; 
 int MPI2_SGE_FLAGS_LAST_ELEMENT ; 
 int MPI2_SGE_FLAGS_SHIFT ; 
 int MPI2_SGE_FLAGS_SIMPLE_ELEMENT ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ,int) ; 

void
mpt2sas_base_build_zero_len_sge(struct MPT2SAS_ADAPTER *ioc, void *paddr)
{
	u32 flags_length = (u32)((MPI2_SGE_FLAGS_LAST_ELEMENT |
	    MPI2_SGE_FLAGS_END_OF_BUFFER | MPI2_SGE_FLAGS_END_OF_LIST |
	    MPI2_SGE_FLAGS_SIMPLE_ELEMENT) <<
	    MPI2_SGE_FLAGS_SHIFT);
	ioc->base_add_sg_single(paddr, flags_length, -1);
}