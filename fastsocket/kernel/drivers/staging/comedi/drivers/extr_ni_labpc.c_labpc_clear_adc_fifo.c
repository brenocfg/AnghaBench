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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_byte ) (scalar_t__) ;int /*<<< orphan*/  (* write_byte ) (int,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ ADC_CLEAR_REG ; 
 scalar_t__ ADC_FIFO_REG ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  stub1 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 

__attribute__((used)) static void labpc_clear_adc_fifo(const struct comedi_device *dev)
{
	devpriv->write_byte(0x1, dev->iobase + ADC_CLEAR_REG);
	devpriv->read_byte(dev->iobase + ADC_FIFO_REG);
	devpriv->read_byte(dev->iobase + ADC_FIFO_REG);
}