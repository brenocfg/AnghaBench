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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_WCID_ATTRIBUTE_BSS_IDX ; 
 int /*<<< orphan*/  MAC_WCID_ATTRIBUTE_BSS_IDX_EXT ; 
 int MAC_WCID_ATTR_ENTRY (int) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int,int*) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_config_wcid_attr_bssidx(struct rt2x00_dev *rt2x00dev,
					   int wcid, u32 bssidx)
{
	u32 offset = MAC_WCID_ATTR_ENTRY(wcid);
	u32 reg;

	/*
	 * The BSS Idx numbers is split in a main value of 3 bits,
	 * and a extended field for adding one additional bit to the value.
	 */
	rt2800_register_read(rt2x00dev, offset, &reg);
	rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_BSS_IDX, (bssidx & 0x7));
	rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_BSS_IDX_EXT,
			   (bssidx & 0x8) >> 3);
	rt2800_register_write(rt2x00dev, offset, reg);
}