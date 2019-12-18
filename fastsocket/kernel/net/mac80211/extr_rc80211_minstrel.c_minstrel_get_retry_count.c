#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct minstrel_rate {unsigned int adjusted_retry_count; int /*<<< orphan*/  retry_count_cts; int /*<<< orphan*/  retry_count_rtscts; } ;
struct TYPE_2__ {scalar_t__ use_cts_prot; scalar_t__ use_rts; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;

/* Variables and functions */
 unsigned int max (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline unsigned int
minstrel_get_retry_count(struct minstrel_rate *mr,
                         struct ieee80211_tx_info *info)
{
	unsigned int retry = mr->adjusted_retry_count;

	if (info->control.use_rts)
		retry = max(2U, min(mr->retry_count_rtscts, retry));
	else if (info->control.use_cts_prot)
		retry = max(2U, min(mr->retry_count_cts, retry));
	return retry;
}