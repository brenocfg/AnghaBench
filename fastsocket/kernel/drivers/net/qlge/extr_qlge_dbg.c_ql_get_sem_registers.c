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
typedef  int u32 ;
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int MAX_SEMAPHORE_FUNCTIONS ; 
 int MPI_NIC_FUNCTION_SHIFT ; 
 int MPI_NIC_REG_BLOCK ; 
 int SEM ; 
 int ql_read_mpi_reg (struct ql_adapter*,int,int*) ; 

__attribute__((used)) static void ql_get_sem_registers(struct ql_adapter *qdev, u32 *buf)
{
	u32 func_num, reg, reg_val;
	int status;

	for (func_num = 0; func_num < MAX_SEMAPHORE_FUNCTIONS ; func_num++) {
		reg = MPI_NIC_REG_BLOCK
			| (func_num << MPI_NIC_FUNCTION_SHIFT)
			| (SEM / 4);
		status = ql_read_mpi_reg(qdev, reg, &reg_val);
		*buf = reg_val;
		/* if the read failed then dead fill the element. */
		if (!status)
			*buf = 0xdeadbeef;
		buf++;
	}
}