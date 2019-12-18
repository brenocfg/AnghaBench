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
struct enic {int /*<<< orphan*/  devcmd_lock; } ;

/* Variables and functions */
 int enic_set_nic_cfg (struct enic*,int,int,int,int,int,int const,int const) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enic_set_niccfg(struct enic *enic, u8 rss_default_cpu,
	u8 rss_hash_type, u8 rss_hash_bits, u8 rss_base_cpu, u8 rss_enable)
{
	const u8 tso_ipid_split_en = 0;
	const u8 ig_vlan_strip_en = 1;
	int err;

	/* Enable VLAN tag stripping.
	*/

	spin_lock(&enic->devcmd_lock);
	err = enic_set_nic_cfg(enic,
		rss_default_cpu, rss_hash_type,
		rss_hash_bits, rss_base_cpu,
		rss_enable, tso_ipid_split_en,
		ig_vlan_strip_en);
	spin_unlock(&enic->devcmd_lock);

	return err;
}