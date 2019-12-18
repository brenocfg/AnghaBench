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
struct typhoon {int muted; int /*<<< orphan*/  mutefreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  typhoon_setfreq_generic (struct typhoon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typhoon_setvol_generic (struct typhoon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void typhoon_mute(struct typhoon *dev)
{
	if (dev->muted == 1)
		return;
	typhoon_setvol_generic(dev, 0);
	typhoon_setfreq_generic(dev, dev->mutefreq);
	dev->muted = 1;
}