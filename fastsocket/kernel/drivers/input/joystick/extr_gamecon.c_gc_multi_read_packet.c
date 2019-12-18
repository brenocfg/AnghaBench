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
struct gc {TYPE_1__* pd; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int parport_read_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_write_data (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gc_multi_read_packet(struct gc *gc, int length, unsigned char *data)
{
	int i;

	for (i = 0; i < length; i++) {
		parport_write_data(gc->pd->port, ~(1 << i));
		data[i] = parport_read_status(gc->pd->port) ^ 0x7f;
	}
}