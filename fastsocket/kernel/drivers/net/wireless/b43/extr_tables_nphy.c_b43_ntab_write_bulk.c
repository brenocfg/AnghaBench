#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct b43_wldev {TYPE_1__* dev; } ;
struct TYPE_2__ {int chip_id; int chip_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_TABLE_ADDR ; 
 int /*<<< orphan*/  B43_NPHY_TABLE_DATAHI ; 
 int /*<<< orphan*/  B43_NPHY_TABLE_DATALO ; 
#define  B43_NTAB_16BIT 130 
#define  B43_NTAB_32BIT 129 
#define  B43_NTAB_8BIT 128 
 int B43_NTAB_TYPEMASK ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

void b43_ntab_write_bulk(struct b43_wldev *dev, u32 offset,
			  unsigned int nr_elements, const void *_data)
{
	u32 type, value;
	const u8 *data = _data;
	unsigned int i;

	type = offset & B43_NTAB_TYPEMASK;
	offset &= ~B43_NTAB_TYPEMASK;
	B43_WARN_ON(offset > 0xFFFF);

	b43_phy_write(dev, B43_NPHY_TABLE_ADDR, offset);

	for (i = 0; i < nr_elements; i++) {
		/* Auto increment broken + caching issue on BCM43224? */
		if ((offset >> 10) == 9 && dev->dev->chip_id == 43224 &&
		    dev->dev->chip_rev == 1) {
			b43_phy_read(dev, B43_NPHY_TABLE_DATALO);
			b43_phy_write(dev, B43_NPHY_TABLE_ADDR, offset + i);
		}

		switch (type) {
		case B43_NTAB_8BIT:
			value = *data;
			data++;
			B43_WARN_ON(value & ~0xFF);
			b43_phy_write(dev, B43_NPHY_TABLE_DATALO, value);
			break;
		case B43_NTAB_16BIT:
			value = *((u16 *)data);
			data += 2;
			B43_WARN_ON(value & ~0xFFFF);
			b43_phy_write(dev, B43_NPHY_TABLE_DATALO, value);
			break;
		case B43_NTAB_32BIT:
			value = *((u32 *)data);
			data += 4;
			b43_phy_write(dev, B43_NPHY_TABLE_DATAHI, value >> 16);
			b43_phy_write(dev, B43_NPHY_TABLE_DATALO,
					value & 0xFFFF);
			break;
		default:
			B43_WARN_ON(1);
		}
	}
}