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
typedef  int /*<<< orphan*/  u_char ;
struct net_device {int dummy; } ;
struct iw_quality {int level; int noise; int qual; int updated; } ;

/* Variables and functions */
 int IW_QUAL_ALL_UPDATED ; 
 int IW_QUAL_DBM ; 
 int /*<<< orphan*/  wireless_spy_update (struct net_device*,int /*<<< orphan*/ *,struct iw_quality*) ; 

__attribute__((used)) static inline void orinoco_spy_gather(struct net_device *dev, u_char *mac,
				      int level, int noise)
{
	struct iw_quality wstats;
	wstats.level = level - 0x95;
	wstats.noise = noise - 0x95;
	wstats.qual = (level > noise) ? (level - noise) : 0;
	wstats.updated = IW_QUAL_ALL_UPDATED | IW_QUAL_DBM;
	/* Update spy records */
	wireless_spy_update(dev, mac, &wstats);
}