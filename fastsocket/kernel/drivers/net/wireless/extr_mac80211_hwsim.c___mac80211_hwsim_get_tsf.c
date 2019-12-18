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
typedef  scalar_t__ u64 ;
struct mac80211_hwsim_data {scalar_t__ tsf_offset; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 scalar_t__ mac80211_hwsim_get_tsf_raw () ; 

__attribute__((used)) static __le64 __mac80211_hwsim_get_tsf(struct mac80211_hwsim_data *data)
{
	u64 now = mac80211_hwsim_get_tsf_raw();
	return cpu_to_le64(now + data->tsf_offset);
}