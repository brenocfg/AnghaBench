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
struct llinfo_arp {int /*<<< orphan*/  la_lastused; int /*<<< orphan*/ * la_llreach; } ;

/* Variables and functions */
 int /*<<< orphan*/  net_uptime () ; 

__attribute__((used)) static __inline void
arp_llreach_use(struct llinfo_arp *la)
{
	if (la->la_llreach != NULL)
		la->la_lastused = net_uptime();
}