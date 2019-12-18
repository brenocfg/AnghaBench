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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_is_all_idle () ; 
 int /*<<< orphan*/  regulatory_hint_disconnect () ; 

__attribute__((used)) static void disconnect_work(struct work_struct *work)
{
	if (!cfg80211_is_all_idle())
		return;

	regulatory_hint_disconnect();
}