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
struct cmac {int /*<<< orphan*/  adapter; TYPE_1__* instance; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_MTU ; 
 int /*<<< orphan*/  REG_MAX_LEN (int) ; 
 int /*<<< orphan*/  vsc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mac_set_mtu(struct cmac *mac, int mtu)
{
	int port = mac->instance->index;

	if (mtu > MAX_MTU)
		return -EINVAL;

	/* max_len includes header and FCS */
	vsc_write(mac->adapter, REG_MAX_LEN(port), mtu + 14 + 4);
	return 0;
}