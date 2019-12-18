#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ctlr_info {scalar_t__ vaddr; TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  lower; } ;
struct TYPE_6__ {TYPE_2__ Tag; } ;
struct CommandList {int /*<<< orphan*/  busaddr; TYPE_3__ Header; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SA5_REQUEST_PORT_OFFSET ; 
 scalar_t__ SA5_SCRATCHPAD_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void SA5_submit_command(struct ctlr_info *h,
	struct CommandList *c)
{
	dev_dbg(&h->pdev->dev, "Sending %x, tag = %x\n", c->busaddr,
		c->Header.Tag.lower);
	writel(c->busaddr, h->vaddr + SA5_REQUEST_PORT_OFFSET);
	(void) readl(h->vaddr + SA5_SCRATCHPAD_OFFSET);
}