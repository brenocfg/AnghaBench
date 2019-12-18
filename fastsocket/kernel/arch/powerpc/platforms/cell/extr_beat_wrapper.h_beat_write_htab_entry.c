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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  HV_write_htab_entry ; 
 int /*<<< orphan*/  beat_hcall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline s64 beat_write_htab_entry(u64 htab_id, u64 slot,
	u64 hpte_v, u64 hpte_r, u64 mask_v, u64 mask_r,
	u64 *ret_v, u64 *ret_r)
{
	u64 dummy[2];
	s64 ret;

	ret = beat_hcall2(HV_write_htab_entry, dummy, htab_id, slot,
		hpte_v, hpte_r, mask_v, mask_r);
	*ret_v = dummy[0];
	*ret_r = dummy[1];
	return ret;
}