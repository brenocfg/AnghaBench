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
 int /*<<< orphan*/  HV_insert_htab_entry3 ; 
 int /*<<< orphan*/  beat_hcall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline s64 beat_insert_htab_entry3(u64 htab_id, u64 group,
	u64 hpte_v, u64 hpte_r, u64 mask_v, u64 value_v, u64 *slot)
{
	u64 dummy[1];
	s64 ret;

	ret = beat_hcall1(HV_insert_htab_entry3, dummy, htab_id, group,
		hpte_v, hpte_r, mask_v, value_v);
	*slot = dummy[0];
	return ret;
}