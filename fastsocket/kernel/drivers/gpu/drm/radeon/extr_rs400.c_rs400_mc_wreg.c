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
struct radeon_device {int dummy; } ;
typedef  int reg ;

/* Variables and functions */
 int /*<<< orphan*/  RS480_NB_MC_DATA ; 
 int /*<<< orphan*/  RS480_NB_MC_INDEX ; 
 int RS480_NB_MC_IND_WR_EN ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

void rs400_mc_wreg(struct radeon_device *rdev, uint32_t reg, uint32_t v)
{
	WREG32(RS480_NB_MC_INDEX, ((reg) & 0xff) | RS480_NB_MC_IND_WR_EN);
	WREG32(RS480_NB_MC_DATA, (v));
	WREG32(RS480_NB_MC_INDEX, 0xff);
}