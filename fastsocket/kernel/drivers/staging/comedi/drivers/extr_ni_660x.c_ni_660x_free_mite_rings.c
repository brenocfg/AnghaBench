#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_4__ {unsigned int n_chips; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** mite_rings; } ;

/* Variables and functions */
 TYPE_2__* board (struct comedi_device*) ; 
 unsigned int counters_per_chip ; 
 int /*<<< orphan*/  mite_free_ring (int /*<<< orphan*/ ) ; 
 TYPE_1__* private (struct comedi_device*) ; 

__attribute__((used)) static void ni_660x_free_mite_rings(struct comedi_device *dev)
{
	unsigned i;
	unsigned j;

	for (i = 0; i < board(dev)->n_chips; ++i) {
		for (j = 0; j < counters_per_chip; ++j) {
			mite_free_ring(private(dev)->mite_rings[i][j]);
		}
	}
}