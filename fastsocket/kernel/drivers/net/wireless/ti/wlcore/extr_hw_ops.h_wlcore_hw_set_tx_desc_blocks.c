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
struct wl1271_tx_hw_descr {int dummy; } ;
struct wl1271 {TYPE_1__* ops; } ;
struct TYPE_2__ {void (* set_tx_desc_blocks ) (struct wl1271*,struct wl1271_tx_hw_descr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void stub1 (struct wl1271*,struct wl1271_tx_hw_descr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
wlcore_hw_set_tx_desc_blocks(struct wl1271 *wl, struct wl1271_tx_hw_descr *desc,
			     u32 blks, u32 spare_blks)
{
	if (!wl->ops->set_tx_desc_blocks)
		BUG_ON(1);

	return wl->ops->set_tx_desc_blocks(wl, desc, blks, spare_blks);
}