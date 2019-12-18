#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int CHIP_RS600 ; 
 int CHIP_RS690 ; 
 int CHIP_RS740 ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RS480_READ_MCIND (TYPE_1__*,int) ; 
 int /*<<< orphan*/  RS600_READ_MCIND (TYPE_1__*,int) ; 
 int /*<<< orphan*/  RS690_READ_MCIND (TYPE_1__*,int) ; 

__attribute__((used)) static u32 IGP_READ_MCIND(drm_radeon_private_t *dev_priv, int addr)
{
	if (((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS690) ||
	    ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS740))
		return RS690_READ_MCIND(dev_priv, addr);
	else if ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_RS600)
		return RS600_READ_MCIND(dev_priv, addr);
	else
		return RS480_READ_MCIND(dev_priv, addr);
}