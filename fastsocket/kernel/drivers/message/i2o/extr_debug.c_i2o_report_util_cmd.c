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

/* Variables and functions */
#define  I2O_CMD_UTIL_ABORT 141 
#define  I2O_CMD_UTIL_CLAIM 140 
#define  I2O_CMD_UTIL_CONFIG_DIALOG 139 
#define  I2O_CMD_UTIL_DEVICE_RELEASE 138 
#define  I2O_CMD_UTIL_DEVICE_RESERVE 137 
#define  I2O_CMD_UTIL_EVT_ACK 136 
#define  I2O_CMD_UTIL_EVT_REGISTER 135 
#define  I2O_CMD_UTIL_LOCK 134 
#define  I2O_CMD_UTIL_LOCK_RELEASE 133 
#define  I2O_CMD_UTIL_NOP 132 
#define  I2O_CMD_UTIL_PARAMS_GET 131 
#define  I2O_CMD_UTIL_PARAMS_SET 130 
#define  I2O_CMD_UTIL_RELEASE 129 
#define  I2O_CMD_UTIL_REPLY_FAULT_NOTIFY 128 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void i2o_report_util_cmd(u8 cmd)
{
	switch (cmd) {
	case I2O_CMD_UTIL_NOP:
		printk("UTIL_NOP, ");
		break;
	case I2O_CMD_UTIL_ABORT:
		printk("UTIL_ABORT, ");
		break;
	case I2O_CMD_UTIL_CLAIM:
		printk("UTIL_CLAIM, ");
		break;
	case I2O_CMD_UTIL_RELEASE:
		printk("UTIL_CLAIM_RELEASE, ");
		break;
	case I2O_CMD_UTIL_CONFIG_DIALOG:
		printk("UTIL_CONFIG_DIALOG, ");
		break;
	case I2O_CMD_UTIL_DEVICE_RESERVE:
		printk("UTIL_DEVICE_RESERVE, ");
		break;
	case I2O_CMD_UTIL_DEVICE_RELEASE:
		printk("UTIL_DEVICE_RELEASE, ");
		break;
	case I2O_CMD_UTIL_EVT_ACK:
		printk("UTIL_EVENT_ACKNOWLEDGE, ");
		break;
	case I2O_CMD_UTIL_EVT_REGISTER:
		printk("UTIL_EVENT_REGISTER, ");
		break;
	case I2O_CMD_UTIL_LOCK:
		printk("UTIL_LOCK, ");
		break;
	case I2O_CMD_UTIL_LOCK_RELEASE:
		printk("UTIL_LOCK_RELEASE, ");
		break;
	case I2O_CMD_UTIL_PARAMS_GET:
		printk("UTIL_PARAMS_GET, ");
		break;
	case I2O_CMD_UTIL_PARAMS_SET:
		printk("UTIL_PARAMS_SET, ");
		break;
	case I2O_CMD_UTIL_REPLY_FAULT_NOTIFY:
		printk("UTIL_REPLY_FAULT_NOTIFY, ");
		break;
	default:
		printk("Cmd = %0#2x, ", cmd);
	}
}