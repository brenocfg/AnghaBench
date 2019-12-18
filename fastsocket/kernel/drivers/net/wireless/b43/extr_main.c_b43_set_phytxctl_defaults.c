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
typedef  int /*<<< orphan*/  u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int /*<<< orphan*/  B43_SHM_SH_ACKCTSPHYCTL ; 
 int /*<<< orphan*/  B43_SHM_SH_BEACPHYCTL ; 
 int /*<<< orphan*/  B43_SHM_SH_PRPHYCTL ; 
 int /*<<< orphan*/  B43_TXH_PHY_ANT01AUTO ; 
 int /*<<< orphan*/  B43_TXH_PHY_ENC_CCK ; 
 int /*<<< orphan*/  B43_TXH_PHY_TXPWR ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_set_phytxctl_defaults(struct b43_wldev *dev)
{
	u16 ctl = 0;

	ctl |= B43_TXH_PHY_ENC_CCK;
	ctl |= B43_TXH_PHY_ANT01AUTO;
	ctl |= B43_TXH_PHY_TXPWR;

	b43_shm_write16(dev, B43_SHM_SHARED, B43_SHM_SH_BEACPHYCTL, ctl);
	b43_shm_write16(dev, B43_SHM_SHARED, B43_SHM_SH_ACKCTSPHYCTL, ctl);
	b43_shm_write16(dev, B43_SHM_SHARED, B43_SHM_SH_PRPHYCTL, ctl);
}