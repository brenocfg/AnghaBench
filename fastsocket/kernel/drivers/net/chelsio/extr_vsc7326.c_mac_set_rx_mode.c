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
typedef  int u32 ;
struct t1_rx_mode {int dummy; } ;
struct cmac {int /*<<< orphan*/  adapter; TYPE_1__* instance; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ING_FFILT_UM_EN ; 
 scalar_t__ t1_rx_mode_promisc (struct t1_rx_mode*) ; 
 int /*<<< orphan*/  vsc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vsc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mac_set_rx_mode(struct cmac *mac, struct t1_rx_mode *rm)
{
	u32 v;
	int port = mac->instance->index;

	vsc_read(mac->adapter, REG_ING_FFILT_UM_EN, &v);
	v |= 1 << 12;

	if (t1_rx_mode_promisc(rm))
		v &= ~(1 << (port + 16));
	else
		v |= 1 << (port + 16);

	vsc_write(mac->adapter, REG_ING_FFILT_UM_EN, v);
	return 0;
}