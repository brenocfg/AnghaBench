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
struct TYPE_2__ {int n_chips; } ;

/* Variables and functions */
 TYPE_1__* board (struct comedi_device*) ; 
 int counters_per_chip ; 

__attribute__((used)) static inline unsigned ni_660x_num_counters(struct comedi_device *dev)
{
	return board(dev)->n_chips * counters_per_chip;
}