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

/* Variables and functions */
 int /*<<< orphan*/  CAN_TX_IDX ; 
 int /*<<< orphan*/  TX_GPIO_NUM ; 
 int /*<<< orphan*/  gpio_matrix_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void invert_tx_bits(bool enable)
{
    if (enable) {
        //Inverts output of TX to trigger errors
        gpio_matrix_out(TX_GPIO_NUM, CAN_TX_IDX, true, false);
    } else {
        //Returns TX to default settings
        gpio_matrix_out(TX_GPIO_NUM, CAN_TX_IDX, false, false);
    }
}