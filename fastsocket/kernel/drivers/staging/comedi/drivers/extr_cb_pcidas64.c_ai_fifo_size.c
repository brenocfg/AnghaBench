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
struct comedi_device {int dummy; } ;
struct TYPE_6__ {TYPE_1__* ai_fifo; } ;
struct TYPE_5__ {unsigned int ai_fifo_segment_length; } ;
struct TYPE_4__ {unsigned int num_segments; unsigned int sample_packing_ratio; } ;

/* Variables and functions */
 TYPE_3__* board (struct comedi_device*) ; 
 TYPE_2__* priv (struct comedi_device*) ; 

__attribute__((used)) static unsigned int ai_fifo_size(struct comedi_device *dev)
{
	return priv(dev)->ai_fifo_segment_length *
	    board(dev)->ai_fifo->num_segments *
	    board(dev)->ai_fifo->sample_packing_ratio;
}