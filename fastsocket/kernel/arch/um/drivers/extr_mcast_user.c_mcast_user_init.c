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
struct mcast_data {void* dev; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  mcast_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  new_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcast_user_init(void *data, void *dev)
{
	struct mcast_data *pri = data;

	pri->mcast_addr = new_addr(pri->addr, pri->port);
	pri->dev = dev;
	return 0;
}