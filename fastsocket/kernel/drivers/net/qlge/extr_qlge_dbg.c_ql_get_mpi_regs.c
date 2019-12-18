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
 int ql_read_mpi_reg (struct ql_adapter*,int,int*) ; 

__attribute__((used)) static int ql_get_mpi_regs(struct ql_adapter *qdev, u32 *buf,
				u32 offset, u32 count)
{
	int i, status = 0;
	for (i = 0; i < count; i++, buf++) {
		status = ql_read_mpi_reg(qdev, offset + i, buf);
		if (status)
			return status;
	}
	return status;
}