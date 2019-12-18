#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  waiting; TYPE_4__* cur_cmd; TYPE_2__* dev; int /*<<< orphan*/  base; } ;
typedef  TYPE_5__ ppa_struct ;
struct TYPE_9__ {int phase; } ;
struct TYPE_10__ {TYPE_3__ SCp; } ;
struct TYPE_8__ {TYPE_1__* port; } ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void got_it(ppa_struct *dev)
{
	dev->base = dev->dev->port->base;
	if (dev->cur_cmd)
		dev->cur_cmd->SCp.phase = 1;
	else
		wake_up(dev->waiting);
}