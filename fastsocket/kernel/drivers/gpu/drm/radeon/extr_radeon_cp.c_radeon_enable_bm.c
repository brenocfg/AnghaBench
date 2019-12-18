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
struct drm_radeon_private {int flags; } ;

/* Variables and functions */
 int CHIP_R420 ; 
 int CHIP_RS400 ; 
 int CHIP_RS480 ; 
 int CHIP_RS690 ; 
 int CHIP_RS740 ; 
 int CHIP_RV350 ; 
 int /*<<< orphan*/  RADEON_BUS_CNTL ; 
 int RADEON_BUS_MASTER_DIS ; 
 int RADEON_FAMILY_MASK ; 
 int RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int) ; 
 int RS600_BUS_MASTER_DIS ; 

void radeon_enable_bm(struct drm_radeon_private *dev_priv)
{
	u32 tmp;
	/* Turn on bus mastering */
	if (((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS690) ||
	    ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS740)) {
		/* rs600/rs690/rs740 */
		tmp = RADEON_READ(RADEON_BUS_CNTL) & ~RS600_BUS_MASTER_DIS;
		RADEON_WRITE(RADEON_BUS_CNTL, tmp);
	} else if (((dev_priv->flags & RADEON_FAMILY_MASK) <= CHIP_RV350) ||
		   ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_R420) ||
		   ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS400) ||
		   ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS480)) {
		/* r1xx, r2xx, r300, r(v)350, r420/r481, rs400/rs480 */
		tmp = RADEON_READ(RADEON_BUS_CNTL) & ~RADEON_BUS_MASTER_DIS;
		RADEON_WRITE(RADEON_BUS_CNTL, tmp);
	} /* PCIE cards appears to not need this */
}