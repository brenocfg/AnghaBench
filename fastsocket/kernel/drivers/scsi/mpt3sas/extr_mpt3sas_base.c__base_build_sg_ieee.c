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
typedef  int u8 ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sge_size_ieee; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int MPI25_IEEE_SGE_FLAGS_END_OF_LIST ; 
 int MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT ; 
 int MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR ; 
 int /*<<< orphan*/  _base_add_sg_single_ieee (void*,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _base_build_zero_len_sge_ieee (struct MPT3SAS_ADAPTER*,void*) ; 

__attribute__((used)) static void
_base_build_sg_ieee(struct MPT3SAS_ADAPTER *ioc, void *psge,
	dma_addr_t data_out_dma, size_t data_out_sz, dma_addr_t data_in_dma,
	size_t data_in_sz)
{
	u8 sgl_flags;

	if (!data_out_sz && !data_in_sz) {
		_base_build_zero_len_sge_ieee(ioc, psge);
		return;
	}

	if (data_out_sz && data_in_sz) {
		/* WRITE sgel first */
		sgl_flags = MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_out_sz,
		    data_out_dma);

		/* incr sgel */
		psge += ioc->sge_size_ieee;

		/* READ sgel last */
		sgl_flags |= MPI25_IEEE_SGE_FLAGS_END_OF_LIST;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_in_sz,
		    data_in_dma);
	} else if (data_out_sz) /* WRITE */ {
		sgl_flags = MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI25_IEEE_SGE_FLAGS_END_OF_LIST |
		    MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_out_sz,
		    data_out_dma);
	} else if (data_in_sz) /* READ */ {
		sgl_flags = MPI2_IEEE_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI25_IEEE_SGE_FLAGS_END_OF_LIST |
		    MPI2_IEEE_SGE_FLAGS_SYSTEM_ADDR;
		_base_add_sg_single_ieee(psge, sgl_flags, 0, data_in_sz,
		    data_in_dma);
	}
}