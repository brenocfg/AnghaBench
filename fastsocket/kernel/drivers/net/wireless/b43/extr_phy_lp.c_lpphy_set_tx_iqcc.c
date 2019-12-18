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
 int /*<<< orphan*/  B43_LPTAB16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_lptab_write_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lpphy_set_tx_iqcc(struct b43_wldev *dev, u16 a, u16 b)
{
	u16 tmp[2];

	tmp[0] = a;
	tmp[1] = b;
	b43_lptab_write_bulk(dev, B43_LPTAB16(0, 80), 2, tmp);
}