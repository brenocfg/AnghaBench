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
struct inpcb {int /*<<< orphan*/  inp_nw_activity; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_stat_set_activity_bitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_uptime () ; 

inline void
inp_set_activity_bitmap(struct inpcb *inp)
{
	in_stat_set_activity_bitmap(&inp->inp_nw_activity, net_uptime());
}