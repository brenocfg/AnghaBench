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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ layout; } ;

/* Variables and functions */
 scalar_t__ LAYOUT_4020 ; 
 TYPE_1__* board (struct comedi_device*) ; 
 int /*<<< orphan*/  pio_drain_ai_fifo_16 (struct comedi_device*) ; 
 int /*<<< orphan*/  pio_drain_ai_fifo_32 (struct comedi_device*) ; 

__attribute__((used)) static void pio_drain_ai_fifo(struct comedi_device *dev)
{
	if (board(dev)->layout == LAYOUT_4020) {
		pio_drain_ai_fifo_32(dev);
	} else
		pio_drain_ai_fifo_16(dev);
}