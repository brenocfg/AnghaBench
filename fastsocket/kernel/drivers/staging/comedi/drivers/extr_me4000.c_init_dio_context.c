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
struct TYPE_3__ {scalar_t__ port_3_reg; scalar_t__ port_2_reg; scalar_t__ port_1_reg; scalar_t__ port_0_reg; scalar_t__ ctrl_reg; scalar_t__ dir_reg; } ;
struct TYPE_4__ {scalar_t__ me4000_regbase; TYPE_1__ dio_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_PDEBUG (char*) ; 
 scalar_t__ ME4000_DIO_CTRL_REG ; 
 scalar_t__ ME4000_DIO_DIR_REG ; 
 scalar_t__ ME4000_DIO_PORT_0_REG ; 
 scalar_t__ ME4000_DIO_PORT_1_REG ; 
 scalar_t__ ME4000_DIO_PORT_2_REG ; 
 scalar_t__ ME4000_DIO_PORT_3_REG ; 
 TYPE_2__* info ; 

__attribute__((used)) static int init_dio_context(struct comedi_device *dev)
{

	CALL_PDEBUG("In init_dio_context()\n");

	info->dio_context.dir_reg = info->me4000_regbase + ME4000_DIO_DIR_REG;
	info->dio_context.ctrl_reg = info->me4000_regbase + ME4000_DIO_CTRL_REG;
	info->dio_context.port_0_reg =
	    info->me4000_regbase + ME4000_DIO_PORT_0_REG;
	info->dio_context.port_1_reg =
	    info->me4000_regbase + ME4000_DIO_PORT_1_REG;
	info->dio_context.port_2_reg =
	    info->me4000_regbase + ME4000_DIO_PORT_2_REG;
	info->dio_context.port_3_reg =
	    info->me4000_regbase + ME4000_DIO_PORT_3_REG;

	return 0;
}