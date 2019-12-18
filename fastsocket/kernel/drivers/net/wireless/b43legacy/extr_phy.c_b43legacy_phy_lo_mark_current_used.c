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
struct b43legacy_wldev {int dummy; } ;
struct b43legacy_lopair {int used; } ;

/* Variables and functions */
 struct b43legacy_lopair* b43legacy_current_lopair (struct b43legacy_wldev*) ; 

__attribute__((used)) static
void b43legacy_phy_lo_mark_current_used(struct b43legacy_wldev *dev)
{
	struct b43legacy_lopair *pair;

	pair = b43legacy_current_lopair(dev);
	pair->used = 1;
}