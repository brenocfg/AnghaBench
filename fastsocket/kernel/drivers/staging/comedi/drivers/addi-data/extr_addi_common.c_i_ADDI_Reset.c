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
struct TYPE_2__ {int /*<<< orphan*/  (* i_hwdrv_Reset ) (struct comedi_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct comedi_device*) ; 
 TYPE_1__* this_board ; 

__attribute__((used)) static int i_ADDI_Reset(struct comedi_device *dev)
{

	this_board->i_hwdrv_Reset(dev);
	return 0;
}