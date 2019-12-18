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
struct regulatory_request {int dummy; } ;
struct ieee80211_regdomain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ieee80211_regdomain const* cfg80211_world_regdom ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  reset_regdomains (int,struct ieee80211_regdomain const*) ; 

__attribute__((used)) static void update_world_regdomain(const struct ieee80211_regdomain *rd)
{
	struct regulatory_request *lr;

	lr = get_last_request();

	WARN_ON(!lr);

	reset_regdomains(false, rd);

	cfg80211_world_regdom = rd;
}