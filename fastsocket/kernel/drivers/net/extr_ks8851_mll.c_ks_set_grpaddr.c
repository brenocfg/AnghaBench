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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ks_net {size_t* mcast_bits; size_t mcast_lst_size; int /*<<< orphan*/ * mcast_lst; } ;

/* Variables and functions */
 int HW_MCAST_SIZE ; 
 size_t KS_MAHTR0 ; 
 int ether_gen_crc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ks_set_grpaddr(struct ks_net *ks)
{
	u8	i;
	u32	index, position, value;

	memset(ks->mcast_bits, 0, sizeof(u8) * HW_MCAST_SIZE);

	for (i = 0; i < ks->mcast_lst_size; i++) {
		position = (ether_gen_crc(6, ks->mcast_lst[i]) >> 26) & 0x3f;
		index = position >> 3;
		value = 1 << (position & 7);
		ks->mcast_bits[index] |= (u8)value;
	}

	for (i  = 0; i < HW_MCAST_SIZE; i++) {
		if (i & 1) {
			ks_wrreg16(ks, (u16)((KS_MAHTR0 + i) & ~1),
				(ks->mcast_bits[i] << 8) |
				ks->mcast_bits[i - 1]);
		}
	}
}