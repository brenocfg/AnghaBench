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
struct wl12xx_priv {int dummy; } ;
struct wl12xx_event_mailbox {int dummy; } ;
struct wl1271 {int /*<<< orphan*/  ptable; int /*<<< orphan*/ * ops; } ;
struct platform_device {int dummy; } ;
struct ieee80211_hw {struct wl1271* priv; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ieee80211_hw*) ; 
 int PTR_ERR (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  WL12XX_AGGR_BUFFER_SIZE ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int /*<<< orphan*/  wl12xx_ops ; 
 int /*<<< orphan*/  wl12xx_ptable ; 
 struct ieee80211_hw* wlcore_alloc_hw (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlcore_free_hw (struct wl1271*) ; 
 int wlcore_probe (struct wl1271*,struct platform_device*) ; 

__attribute__((used)) static int wl12xx_probe(struct platform_device *pdev)
{
	struct wl1271 *wl;
	struct ieee80211_hw *hw;
	int ret;

	hw = wlcore_alloc_hw(sizeof(struct wl12xx_priv),
			     WL12XX_AGGR_BUFFER_SIZE,
			     sizeof(struct wl12xx_event_mailbox));
	if (IS_ERR(hw)) {
		wl1271_error("can't allocate hw");
		ret = PTR_ERR(hw);
		goto out;
	}

	wl = hw->priv;
	wl->ops = &wl12xx_ops;
	wl->ptable = wl12xx_ptable;
	ret = wlcore_probe(wl, pdev);
	if (ret)
		goto out_free;

	return ret;

out_free:
	wlcore_free_hw(wl);
out:
	return ret;
}