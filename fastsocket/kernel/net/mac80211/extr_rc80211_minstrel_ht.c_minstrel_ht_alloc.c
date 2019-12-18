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
struct ieee80211_hw {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {void* (* alloc ) (struct ieee80211_hw*,struct dentry*) ;} ;

/* Variables and functions */
 TYPE_1__ mac80211_minstrel ; 
 void* stub1 (struct ieee80211_hw*,struct dentry*) ; 

__attribute__((used)) static void *
minstrel_ht_alloc(struct ieee80211_hw *hw, struct dentry *debugfsdir)
{
	return mac80211_minstrel.alloc(hw, debugfsdir);
}