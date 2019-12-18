#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct pcmcia_socket {int dummy; } ;
struct pcmcia_device {TYPE_1__* function_config; struct pcmcia_socket* socket; } ;
struct TYPE_4__ {int state; int ConfigBase; } ;
typedef  TYPE_1__ config_t ;
struct TYPE_5__ {int Offset; int Action; int /*<<< orphan*/  Value; } ;
typedef  TYPE_2__ conf_reg_t ;

/* Variables and functions */
 int CONFIG_LOCKED ; 
#define  CS_READ 129 
#define  CS_WRITE 128 
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  pcmcia_read_cis_mem (struct pcmcia_socket*,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_write_cis_mem (struct pcmcia_socket*,int,int,int,int /*<<< orphan*/ *) ; 

int pcmcia_access_configuration_register(struct pcmcia_device *p_dev,
					 conf_reg_t *reg)
{
	struct pcmcia_socket *s;
	config_t *c;
	int addr;
	u_char val;

	if (!p_dev || !p_dev->function_config)
		return -EINVAL;

	s = p_dev->socket;
	c = p_dev->function_config;

	if (!(c->state & CONFIG_LOCKED))
		return -EACCES;

	addr = (c->ConfigBase + reg->Offset) >> 1;

	switch (reg->Action) {
	case CS_READ:
		pcmcia_read_cis_mem(s, 1, addr, 1, &val);
		reg->Value = val;
		break;
	case CS_WRITE:
		val = reg->Value;
		pcmcia_write_cis_mem(s, 1, addr, 1, &val);
		break;
	default:
		return -EINVAL;
		break;
	}
	return 0;
}