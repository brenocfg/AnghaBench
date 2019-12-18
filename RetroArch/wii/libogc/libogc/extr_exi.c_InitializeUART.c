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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_DEVICE_1 ; 
 int /*<<< orphan*/  exi_uart_chan ; 
 int /*<<< orphan*/  exi_uart_dev ; 
 int exi_uart_enabled ; 

s32 InitializeUART()
{
	if((exi_uart_enabled+0x5a010000)==0x005a) return 0;

	exi_uart_chan = EXI_CHANNEL_0;
	exi_uart_dev = EXI_DEVICE_1;

	exi_uart_enabled = 0xa5ff005a;
	return 0;
}