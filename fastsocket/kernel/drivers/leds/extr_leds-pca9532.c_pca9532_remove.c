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
struct pca9532_data {int /*<<< orphan*/ * idev; int /*<<< orphan*/  work; TYPE_1__* leds; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  work; int /*<<< orphan*/  ldev; } ;

/* Variables and functions */
#define  PCA9532_TYPE_LED 130 
#define  PCA9532_TYPE_N2100_BEEP 129 
#define  PCA9532_TYPE_NONE 128 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct pca9532_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_free_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pca9532_data*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pca9532_remove(struct i2c_client *client)
{
	struct pca9532_data *data = i2c_get_clientdata(client);
	int i;
	for (i = 0; i < 16; i++)
		switch (data->leds[i].type) {
		case PCA9532_TYPE_NONE:
			break;
		case PCA9532_TYPE_LED:
			led_classdev_unregister(&data->leds[i].ldev);
			cancel_work_sync(&data->leds[i].work);
			break;
		case PCA9532_TYPE_N2100_BEEP:
			if (data->idev != NULL) {
				input_unregister_device(data->idev);
				input_free_device(data->idev);
				cancel_work_sync(&data->work);
				data->idev = NULL;
			}
			break;
		}

	kfree(data);
	i2c_set_clientdata(client, NULL);
	return 0;
}