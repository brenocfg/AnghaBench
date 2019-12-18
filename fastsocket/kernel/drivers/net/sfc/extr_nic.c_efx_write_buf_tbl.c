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
struct efx_nic {TYPE_1__* type; scalar_t__ membase; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;
struct TYPE_2__ {scalar_t__ buf_tbl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_sram_writeq (struct efx_nic*,scalar_t__,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline void efx_write_buf_tbl(struct efx_nic *efx, efx_qword_t *value,
				     unsigned int index)
{
	efx_sram_writeq(efx, efx->membase + efx->type->buf_tbl_base,
			value, index);
}