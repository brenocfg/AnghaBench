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
struct ds2482_w1_chan {int /*<<< orphan*/  channel; struct ds2482_data* pdev; } ;
struct ds2482_data {int w1_count; int /*<<< orphan*/  access_lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2482_CMD_1WIRE_READ_BYTE ; 
 int /*<<< orphan*/  DS2482_PTR_CODE_DATA ; 
 int /*<<< orphan*/  ds2482_select_register (struct ds2482_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds2482_send_cmd (struct ds2482_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds2482_set_channel (struct ds2482_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds2482_wait_1wire_idle (struct ds2482_data*) ; 
 int i2c_smbus_read_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 ds2482_w1_read_byte(void *data)
{
	struct ds2482_w1_chan *pchan = data;
	struct ds2482_data    *pdev = pchan->pdev;
	int result;

	mutex_lock(&pdev->access_lock);

	/* Select the channel */
	ds2482_wait_1wire_idle(pdev);
	if (pdev->w1_count > 1)
		ds2482_set_channel(pdev, pchan->channel);

	/* Send the read byte command */
	ds2482_send_cmd(pdev, DS2482_CMD_1WIRE_READ_BYTE);

	/* Wait until 1WB == 0 */
	ds2482_wait_1wire_idle(pdev);

	/* Select the data register */
	ds2482_select_register(pdev, DS2482_PTR_CODE_DATA);

	/* Read the data byte */
	result = i2c_smbus_read_byte(pdev->client);

	mutex_unlock(&pdev->access_lock);

	return result;
}