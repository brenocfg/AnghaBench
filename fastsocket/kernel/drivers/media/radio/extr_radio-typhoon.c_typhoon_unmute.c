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
struct typhoon {scalar_t__ muted; int /*<<< orphan*/  curvol; int /*<<< orphan*/  curfreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  typhoon_setfreq_generic (struct typhoon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typhoon_setvol_generic (struct typhoon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void typhoon_unmute(struct typhoon *dev)
{
	if (dev->muted == 0)
		return;
	typhoon_setfreq_generic(dev, dev->curfreq);
	typhoon_setvol_generic(dev, dev->curvol);
	dev->muted = 0;
}