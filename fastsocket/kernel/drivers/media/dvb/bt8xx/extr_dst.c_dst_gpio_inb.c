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
struct TYPE_2__ {scalar_t__ value; } ;
union dst_gpio_packet {TYPE_1__ rd; } ;
typedef  scalar_t__ u8 ;
struct dst_state {int /*<<< orphan*/  bt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_ERROR ; 
 int /*<<< orphan*/  DST_IG_READ ; 
 int EREMOTEIO ; 
 int bt878_device_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union dst_gpio_packet*) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int dst_gpio_inb(struct dst_state *state, u8 *result)
{
	union dst_gpio_packet rd_packet;
	int err;

	*result = 0;
	if ((err = bt878_device_control(state->bt, DST_IG_READ, &rd_packet)) < 0) {
		dprintk(verbose, DST_ERROR, 1, "dst_gpio_inb error (err == %i)", err);
		return -EREMOTEIO;
	}
	*result = (u8) rd_packet.rd.value;

	return 0;
}