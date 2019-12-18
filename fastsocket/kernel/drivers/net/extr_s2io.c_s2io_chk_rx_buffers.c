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
struct s2io_nic {int dummy; } ;
struct ring_info {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  INFO_DBG ; 
 int /*<<< orphan*/  fill_rx_buffers (struct s2io_nic*,struct ring_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s2io_chk_rx_buffers(struct s2io_nic *nic, struct ring_info *ring)
{
	if (fill_rx_buffers(nic, ring, 0) == -ENOMEM) {
		DBG_PRINT(INFO_DBG, "%s: Out of memory in Rx Intr!!\n",
			  ring->dev->name);
	}
	return 0;
}