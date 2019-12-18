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
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct mlx4_en_dev {int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timecounter_cyc2time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mlx4_en_fill_hwtstamps(struct mlx4_en_dev *mdev,
			    struct skb_shared_hwtstamps *hwts,
			    u64 timestamp)
{
	u64 nsec;

	nsec = timecounter_cyc2time(&mdev->clock, timestamp);

	memset(hwts, 0, sizeof(struct skb_shared_hwtstamps));
	hwts->hwtstamp = ns_to_ktime(nsec);
}