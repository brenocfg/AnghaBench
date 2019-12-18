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
struct ibmpex_bmc_data {int* tx_msg_data; int rx_msg_len; scalar_t__ rx_result; int /*<<< orphan*/  read_complete; TYPE_1__ tx_message; } ;

/* Variables and functions */
 int ENOENT ; 
 int PEX_GET_SENSOR_NAME ; 
 int /*<<< orphan*/  ibmpex_send_message (struct ibmpex_bmc_data*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmpex_query_sensor_name(struct ibmpex_bmc_data *data, int sensor)
{
	data->tx_msg_data[0] = PEX_GET_SENSOR_NAME;
	data->tx_msg_data[1] = sensor;
	data->tx_message.data_len = 2;
	ibmpex_send_message(data);

	wait_for_completion(&data->read_complete);

	if (data->rx_result || data->rx_msg_len < 1)
		return -ENOENT;

	return 0;
}