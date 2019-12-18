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

/* Variables and functions */
 int MPI_PCICFGCTL_CFGADDR_MASK ; 
 int /*<<< orphan*/  MPI_PCICFGCTL_REG ; 
 int MPI_PCICFGCTL_WRITEEN_MASK ; 
 int /*<<< orphan*/  MPI_PCICFGDATA_REG ; 
 int /*<<< orphan*/  bcm_mpi_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm63xx_int_cfg_writel(u32 val, u32 reg)
{
	u32 tmp;

	tmp = reg & MPI_PCICFGCTL_CFGADDR_MASK;
	tmp |=  MPI_PCICFGCTL_WRITEEN_MASK;
	bcm_mpi_writel(tmp, MPI_PCICFGCTL_REG);
	bcm_mpi_writel(val, MPI_PCICFGDATA_REG);
}