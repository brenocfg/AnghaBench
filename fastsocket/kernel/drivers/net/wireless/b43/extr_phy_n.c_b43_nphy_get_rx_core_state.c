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
typedef  int u8 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_RFSEQCA ; 
 int B43_NPHY_RFSEQCA_RXEN ; 
 int B43_NPHY_RFSEQCA_RXEN_SHIFT ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 b43_nphy_get_rx_core_state(struct b43_wldev *dev)
{
	return (b43_phy_read(dev, B43_NPHY_RFSEQCA) & B43_NPHY_RFSEQCA_RXEN) >>
		B43_NPHY_RFSEQCA_RXEN_SHIFT;
}