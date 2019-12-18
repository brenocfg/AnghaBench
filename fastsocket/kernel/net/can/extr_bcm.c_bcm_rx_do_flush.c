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
struct bcm_op {TYPE_1__* last_frames; } ;
struct TYPE_2__ {int can_dlc; } ;

/* Variables and functions */
 int RX_THR ; 
 int /*<<< orphan*/  bcm_rx_changed (struct bcm_op*,TYPE_1__*) ; 

__attribute__((used)) static inline int bcm_rx_do_flush(struct bcm_op *op, int update,
				  unsigned int index)
{
	if ((op->last_frames) && (op->last_frames[index].can_dlc & RX_THR)) {
		if (update)
			bcm_rx_changed(op, &op->last_frames[index]);
		return 1;
	}
	return 0;
}