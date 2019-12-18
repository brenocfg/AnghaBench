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
typedef  size_t u16 ;
struct ks_net {scalar_t__* mcast_bits; } ;

/* Variables and functions */
 size_t HW_MCAST_SIZE ; 
 scalar_t__ KS_MAHTR0 ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ks_clear_mcast(struct ks_net *ks)
{
	u16	i, mcast_size;
	for (i = 0; i < HW_MCAST_SIZE; i++)
		ks->mcast_bits[i] = 0;

	mcast_size = HW_MCAST_SIZE >> 2;
	for (i = 0; i < mcast_size; i++)
		ks_wrreg16(ks, KS_MAHTR0 + (2*i), 0);
}