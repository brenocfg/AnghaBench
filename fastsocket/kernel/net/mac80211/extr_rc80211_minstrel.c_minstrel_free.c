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
struct minstrel_priv {int /*<<< orphan*/  dbg_fixed_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void
minstrel_free(void *priv)
{
#ifdef CONFIG_MAC80211_DEBUGFS
	debugfs_remove(((struct minstrel_priv *)priv)->dbg_fixed_rate);
#endif
	kfree(priv);
}