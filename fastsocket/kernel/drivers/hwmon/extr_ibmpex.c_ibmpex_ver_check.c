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
struct TYPE_2__ {int data_len; } ;
struct ibmpex_bmc_data {int rx_msg_len; int /*<<< orphan*/  interface; int /*<<< orphan*/ * rx_msg_data; int /*<<< orphan*/  sensor_minor; int /*<<< orphan*/  sensor_major; int /*<<< orphan*/  bmc_device; scalar_t__ rx_result; int /*<<< orphan*/  read_complete; TYPE_1__ tx_message; int /*<<< orphan*/ * tx_msg_data; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  PEX_GET_VERSION ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ibmpex_send_message (struct ibmpex_bmc_data*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmpex_ver_check(struct ibmpex_bmc_data *data)
{
	data->tx_msg_data[0] = PEX_GET_VERSION;
	data->tx_message.data_len = 1;
	ibmpex_send_message(data);

	wait_for_completion(&data->read_complete);

	if (data->rx_result || data->rx_msg_len != 6)
		return -ENOENT;

	data->sensor_major = data->rx_msg_data[0];
	data->sensor_minor = data->rx_msg_data[1];

	dev_info(data->bmc_device, "Found BMC with sensor interface "
		 "v%d.%d %d-%02d-%02d on interface %d\n",
		 data->sensor_major,
		 data->sensor_minor,
		 extract_value(data->rx_msg_data, 2),
		 data->rx_msg_data[4],
		 data->rx_msg_data[5],
		 data->interface);

	return 0;
}