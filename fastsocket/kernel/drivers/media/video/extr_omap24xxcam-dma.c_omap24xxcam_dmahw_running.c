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

/* Variables and functions */
 int /*<<< orphan*/  CAMDMA_CCR (int) ; 
 int CAMDMA_CCR_ENABLE ; 
 int omap24xxcam_reg_in (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap24xxcam_dmahw_running(unsigned long base, int dmach)
{
	return omap24xxcam_reg_in(base, CAMDMA_CCR(dmach)) & CAMDMA_CCR_ENABLE;
}