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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void b43_shm_clear_tssi(struct b43_wldev *dev)
{
	b43_shm_write16(dev, B43_SHM_SHARED, 0x0058, 0x7F7F);
	b43_shm_write16(dev, B43_SHM_SHARED, 0x005a, 0x7F7F);
	b43_shm_write16(dev, B43_SHM_SHARED, 0x0070, 0x7F7F);
	b43_shm_write16(dev, B43_SHM_SHARED, 0x0072, 0x7F7F);
}