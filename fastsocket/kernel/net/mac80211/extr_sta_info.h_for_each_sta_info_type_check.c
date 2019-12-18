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
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int dummy; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline
void for_each_sta_info_type_check(struct ieee80211_local *local,
				  const u8 *addr,
				  struct sta_info *sta,
				  struct sta_info *nxt)
{
}