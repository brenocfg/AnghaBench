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
typedef  scalar_t__ u16 ;
struct b43_wldev {int dummy; } ;
struct b43_phy_ht_channeltab_e_radio2059 {scalar_t__ freq; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct b43_phy_ht_channeltab_e_radio2059*) ; 
 struct b43_phy_ht_channeltab_e_radio2059* b43_phy_ht_channeltab_radio2059 ; 

const struct b43_phy_ht_channeltab_e_radio2059
*b43_phy_ht_get_channeltab_e_r2059(struct b43_wldev *dev, u16 freq)
{
	const struct b43_phy_ht_channeltab_e_radio2059 *e;
	unsigned int i;

	e = b43_phy_ht_channeltab_radio2059;
	for (i = 0; i < ARRAY_SIZE(b43_phy_ht_channeltab_radio2059); i++, e++) {
		if (e->freq == freq)
			return e;
	}

	return NULL;
}