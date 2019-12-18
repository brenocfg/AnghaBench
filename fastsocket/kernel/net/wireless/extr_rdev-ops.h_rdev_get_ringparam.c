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
typedef  int /*<<< orphan*/  u32 ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_ringparam ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_get_ringparam (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_return_void_tx_rx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rdev_get_ringparam(struct cfg80211_registered_device *rdev,
				      u32 *tx, u32 *tx_max, u32 *rx,
				      u32 *rx_max)
{
	trace_rdev_get_ringparam(&rdev->wiphy);
	rdev->ops->get_ringparam(&rdev->wiphy, tx, tx_max, rx, rx_max);
	trace_rdev_return_void_tx_rx(&rdev->wiphy, *tx, *tx_max, *rx, *rx_max);
}