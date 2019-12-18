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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct b43_wldev {scalar_t__ ktp; } ;

/* Variables and functions */
 int B43_SEC_KEYSIZE ; 
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 scalar_t__ B43_SHM_SH_KEYIDXBLOCK ; 
 int b43_kidx_to_fw (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void key_write(struct b43_wldev *dev,
		      u8 index, u8 algorithm, const u8 *key)
{
	unsigned int i;
	u32 offset;
	u16 value;
	u16 kidx;

	/* Key index/algo block */
	kidx = b43_kidx_to_fw(dev, index);
	value = ((kidx << 4) | algorithm);
	b43_shm_write16(dev, B43_SHM_SHARED,
			B43_SHM_SH_KEYIDXBLOCK + (kidx * 2), value);

	/* Write the key to the Key Table Pointer offset */
	offset = dev->ktp + (index * B43_SEC_KEYSIZE);
	for (i = 0; i < B43_SEC_KEYSIZE; i += 2) {
		value = key[i];
		value |= (u16) (key[i + 1]) << 8;
		b43_shm_write16(dev, B43_SHM_SHARED, offset + i, value);
	}
}