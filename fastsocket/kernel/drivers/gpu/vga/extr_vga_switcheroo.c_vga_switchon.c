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
struct vga_switcheroo_client {int /*<<< orphan*/  pwr_state; int /*<<< orphan*/  pdev; TYPE_2__* ops; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__* handler; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_gpu_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* power_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_SWITCHEROO_ON ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ vgasr_priv ; 

__attribute__((used)) static int vga_switchon(struct vga_switcheroo_client *client)
{
	if (vgasr_priv.handler->power_state)
		vgasr_priv.handler->power_state(client->id, VGA_SWITCHEROO_ON);
	/* call the driver callback to turn on device */
	client->ops->set_gpu_state(client->pdev, VGA_SWITCHEROO_ON);
	client->pwr_state = VGA_SWITCHEROO_ON;
	return 0;
}