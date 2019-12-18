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
typedef  scalar_t__ u8 ;
struct rt2x00_dev {int dummy; } ;
struct link_qual {scalar_t__ vgc_level_reg; scalar_t__ vgc_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2400pci_bbp_write (struct rt2x00_dev*,int,scalar_t__) ; 

__attribute__((used)) static inline void rt2400pci_set_vgc(struct rt2x00_dev *rt2x00dev,
				     struct link_qual *qual, u8 vgc_level)
{
	if (qual->vgc_level_reg != vgc_level) {
		rt2400pci_bbp_write(rt2x00dev, 13, vgc_level);
		qual->vgc_level = vgc_level;
		qual->vgc_level_reg = vgc_level;
	}
}