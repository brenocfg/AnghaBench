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
struct w9966_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  W9966_STATE_CLAIMED ; 
 int /*<<< orphan*/  parport_claim_or_block (int /*<<< orphan*/ ) ; 
 scalar_t__ w9966_getState (struct w9966_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w9966_setState (struct w9966_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void w9966_pdev_claim(struct w9966_dev* cam)
{
	if (w9966_getState(cam, W9966_STATE_CLAIMED, W9966_STATE_CLAIMED))
		return;
	parport_claim_or_block(cam->pdev);
	w9966_setState(cam, W9966_STATE_CLAIMED, W9966_STATE_CLAIMED);
}