#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int select; } ;
struct TYPE_4__ {int Length; int /*<<< orphan*/  Opcode; } ;
struct TYPE_6__ {TYPE_2__ SetGpioPin; TYPE_1__ hdr; } ;
struct ngene_command {int in_len; scalar_t__ out_len; TYPE_3__ cmd; } ;
struct ngene {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_GPIO_PIN ; 
 int ngene_command (struct ngene*,struct ngene_command*) ; 

int ngene_command_gpio_set(struct ngene *dev, u8 select, u8 level)
{
	struct ngene_command com;

	com.cmd.hdr.Opcode = CMD_SET_GPIO_PIN;
	com.cmd.hdr.Length = 1;
	com.cmd.SetGpioPin.select = select | (level << 7);
	com.in_len = 1;
	com.out_len = 0;

	return ngene_command(dev, &com);
}