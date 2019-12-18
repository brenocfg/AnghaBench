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
typedef  int uint32_t ;
struct qla_hw_data {int /*<<< orphan*/  fce; scalar_t__* fce_mb; int /*<<< orphan*/  fce_dma; int /*<<< orphan*/  fce_bufs; } ;
struct qla2xxx_fce_chain {int type; int* eregs; void* size; void* addr_h; void* addr_l; void* chain_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_CHAIN_FCE ; 
 scalar_t__ LSD (int /*<<< orphan*/ ) ; 
 scalar_t__ MSD (int /*<<< orphan*/ ) ; 
 int __constant_htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ fce_calc_size (int /*<<< orphan*/ ) ; 
 void* htonl (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int ntohl (void*) ; 

__attribute__((used)) static inline void *
qla25xx_copy_fce(struct qla_hw_data *ha, void *ptr, uint32_t **last_chain)
{
	uint32_t cnt;
	uint32_t *iter_reg;
	struct qla2xxx_fce_chain *fcec = ptr;

	if (!ha->fce)
		return ptr;

	*last_chain = &fcec->type;
	fcec->type = __constant_htonl(DUMP_CHAIN_FCE);
	fcec->chain_size = htonl(sizeof(struct qla2xxx_fce_chain) +
	    fce_calc_size(ha->fce_bufs));
	fcec->size = htonl(fce_calc_size(ha->fce_bufs));
	fcec->addr_l = htonl(LSD(ha->fce_dma));
	fcec->addr_h = htonl(MSD(ha->fce_dma));

	iter_reg = fcec->eregs;
	for (cnt = 0; cnt < 8; cnt++)
		*iter_reg++ = htonl(ha->fce_mb[cnt]);

	memcpy(iter_reg, ha->fce, ntohl(fcec->size));

	return (void *)iter_reg + ntohl(fcec->size);
}