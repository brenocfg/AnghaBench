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
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  B43legacy_SHM_SH_HOSTFHI ; 
 int /*<<< orphan*/  B43legacy_SHM_SH_HOSTFLO ; 
 int b43legacy_shm_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 b43legacy_hf_read(struct b43legacy_wldev *dev)
{
	u32 ret;

	ret = b43legacy_shm_read16(dev, B43legacy_SHM_SHARED,
				   B43legacy_SHM_SH_HOSTFHI);
	ret <<= 16;
	ret |= b43legacy_shm_read16(dev, B43legacy_SHM_SHARED,
				    B43legacy_SHM_SH_HOSTFLO);

	return ret;
}