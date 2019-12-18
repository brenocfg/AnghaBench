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
struct TYPE_2__ {int /*<<< orphan*/  has_dvb; } ;
struct em28xx {int /*<<< orphan*/ * dvb; TYPE_1__ board; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_dvb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_fini(struct em28xx *dev)
{
	if (!dev->board.has_dvb) {
		/* This device does not support the extension */
		return 0;
	}

	if (dev->dvb) {
		unregister_dvb(dev->dvb);
		kfree(dev->dvb);
		dev->dvb = NULL;
	}

	return 0;
}