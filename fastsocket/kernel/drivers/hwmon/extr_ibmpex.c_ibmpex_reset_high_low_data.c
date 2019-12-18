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
struct ibmpex_bmc_data {int /*<<< orphan*/  read_complete; TYPE_1__ tx_message; int /*<<< orphan*/ * tx_msg_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PEX_RESET_HIGH_LOW ; 
 int /*<<< orphan*/  ibmpex_send_message (struct ibmpex_bmc_data*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmpex_reset_high_low_data(struct ibmpex_bmc_data *data)
{
	data->tx_msg_data[0] = PEX_RESET_HIGH_LOW;
	data->tx_message.data_len = 1;
	ibmpex_send_message(data);

	wait_for_completion(&data->read_complete);

	return 0;
}