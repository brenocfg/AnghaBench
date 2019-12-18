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
struct TYPE_4__ {scalar_t__ in_frame; } ;
struct stir_cb {TYPE_3__* netdev; TYPE_1__ rx_buff; int /*<<< orphan*/  rx_urb; scalar_t__ receiving; } ;
struct TYPE_5__ {int /*<<< orphan*/  collisions; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void receive_stop(struct stir_cb *stir)
{
	stir->receiving = 0;
	usb_kill_urb(stir->rx_urb);

	if (stir->rx_buff.in_frame) 
		stir->netdev->stats.collisions++;
}