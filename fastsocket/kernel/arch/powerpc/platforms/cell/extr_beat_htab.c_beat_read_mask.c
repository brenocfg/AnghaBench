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
typedef  int u64 ;

/* Variables and functions */
 unsigned int HPTES_PER_GROUP ; 
 int HPTE_V_BOLTED ; 
 int /*<<< orphan*/  beat_read_htab_entries (int /*<<< orphan*/ ,unsigned int,int*) ; 
 unsigned int htab_hash_mask ; 

__attribute__((used)) static inline unsigned int beat_read_mask(unsigned hpte_group)
{
	unsigned long rmask = 0;
	u64 hpte_v[5];

	beat_read_htab_entries(0, hpte_group + 0, hpte_v);
	if (!(hpte_v[0] & HPTE_V_BOLTED))
		rmask |= 0x8000;
	if (!(hpte_v[1] & HPTE_V_BOLTED))
		rmask |= 0x4000;
	if (!(hpte_v[2] & HPTE_V_BOLTED))
		rmask |= 0x2000;
	if (!(hpte_v[3] & HPTE_V_BOLTED))
		rmask |= 0x1000;
	beat_read_htab_entries(0, hpte_group + 4, hpte_v);
	if (!(hpte_v[0] & HPTE_V_BOLTED))
		rmask |= 0x0800;
	if (!(hpte_v[1] & HPTE_V_BOLTED))
		rmask |= 0x0400;
	if (!(hpte_v[2] & HPTE_V_BOLTED))
		rmask |= 0x0200;
	if (!(hpte_v[3] & HPTE_V_BOLTED))
		rmask |= 0x0100;
	hpte_group = ~hpte_group & (htab_hash_mask * HPTES_PER_GROUP);
	beat_read_htab_entries(0, hpte_group + 0, hpte_v);
	if (!(hpte_v[0] & HPTE_V_BOLTED))
		rmask |= 0x80;
	if (!(hpte_v[1] & HPTE_V_BOLTED))
		rmask |= 0x40;
	if (!(hpte_v[2] & HPTE_V_BOLTED))
		rmask |= 0x20;
	if (!(hpte_v[3] & HPTE_V_BOLTED))
		rmask |= 0x10;
	beat_read_htab_entries(0, hpte_group + 4, hpte_v);
	if (!(hpte_v[0] & HPTE_V_BOLTED))
		rmask |= 0x08;
	if (!(hpte_v[1] & HPTE_V_BOLTED))
		rmask |= 0x04;
	if (!(hpte_v[2] & HPTE_V_BOLTED))
		rmask |= 0x02;
	if (!(hpte_v[3] & HPTE_V_BOLTED))
		rmask |= 0x01;
	return rmask;
}