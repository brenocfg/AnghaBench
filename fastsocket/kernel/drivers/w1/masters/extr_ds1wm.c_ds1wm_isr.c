#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct ds1wm_data {int slave_present; scalar_t__ read_complete; void* read_byte; scalar_t__ write_complete; scalar_t__ reset_complete; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS1WM_DATA ; 
 int /*<<< orphan*/  DS1WM_INT ; 
 int DS1WM_INT_PD ; 
 int DS1WM_INT_PDR ; 
 int DS1WM_INT_RBF ; 
 int DS1WM_INT_TSRE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 void* ds1wm_read_register (struct ds1wm_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ds1wm_isr(int isr, void *data)
{
	struct ds1wm_data *ds1wm_data = data;
	u8 intr = ds1wm_read_register(ds1wm_data, DS1WM_INT);

	ds1wm_data->slave_present = (intr & DS1WM_INT_PDR) ? 0 : 1;

	if ((intr & DS1WM_INT_PD) && ds1wm_data->reset_complete)
		complete(ds1wm_data->reset_complete);

	if ((intr & DS1WM_INT_TSRE) && ds1wm_data->write_complete)
		complete(ds1wm_data->write_complete);

	if (intr & DS1WM_INT_RBF) {
		ds1wm_data->read_byte = ds1wm_read_register(ds1wm_data,
							    DS1WM_DATA);
		if (ds1wm_data->read_complete)
			complete(ds1wm_data->read_complete);
	}

	return IRQ_HANDLED;
}