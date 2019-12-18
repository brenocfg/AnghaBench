#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2o_device {scalar_t__* dev_name; struct i2o_device* prev; struct i2o_device* next; int /*<<< orphan*/ * owner; TYPE_1__* controller; } ;
struct TYPE_3__ {struct i2o_device* devices; } ;
typedef  TYPE_1__ adpt_hba ;

/* Variables and functions */
 int /*<<< orphan*/  adpt_configuration_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adpt_i2o_install_device(adpt_hba* pHba, struct i2o_device *d)
{
	mutex_lock(&adpt_configuration_lock);
	d->controller=pHba;
	d->owner=NULL;
	d->next=pHba->devices;
	d->prev=NULL;
	if (pHba->devices != NULL){
		pHba->devices->prev=d;
	}
	pHba->devices=d;
	*d->dev_name = 0;

	mutex_unlock(&adpt_configuration_lock);
	return 0;
}