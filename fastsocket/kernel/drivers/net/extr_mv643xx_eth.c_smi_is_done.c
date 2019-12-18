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
struct mv643xx_eth_shared_private {scalar_t__ base; } ;

/* Variables and functions */
 int SMI_BUSY ; 
 scalar_t__ SMI_REG ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int smi_is_done(struct mv643xx_eth_shared_private *msp)
{
	return !(readl(msp->base + SMI_REG) & SMI_BUSY);
}