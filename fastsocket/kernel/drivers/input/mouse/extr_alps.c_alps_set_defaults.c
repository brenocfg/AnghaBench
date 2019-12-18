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
struct alps_data {int byte0; int mask0; int x_max; int y_max; int proto_version; int /*<<< orphan*/  flags; void* addr_command; void* nibble_commands; void* set_abs_params; int /*<<< orphan*/  decode_fields; void* process_packet; int /*<<< orphan*/  hw_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPS_DUALPOINT ; 
#define  ALPS_PROTO_V1 132 
#define  ALPS_PROTO_V2 131 
#define  ALPS_PROTO_V3 130 
#define  ALPS_PROTO_V4 129 
#define  ALPS_PROTO_V5 128 
 void* PSMOUSE_CMD_DISABLE ; 
 void* PSMOUSE_CMD_RESET_WRAP ; 
 int /*<<< orphan*/  alps_decode_dolphin ; 
 int /*<<< orphan*/  alps_decode_pinnacle ; 
 int /*<<< orphan*/  alps_hw_init_dolphin_v1 ; 
 int /*<<< orphan*/  alps_hw_init_v1_v2 ; 
 int /*<<< orphan*/  alps_hw_init_v3 ; 
 int /*<<< orphan*/  alps_hw_init_v4 ; 
 void* alps_process_packet_v1_v2 ; 
 void* alps_process_packet_v3 ; 
 void* alps_process_packet_v4 ; 
 void* alps_set_abs_params_mt ; 
 void* alps_set_abs_params_st ; 
 void* alps_v3_nibble_commands ; 
 void* alps_v4_nibble_commands ; 

__attribute__((used)) static void alps_set_defaults(struct alps_data *priv)
{
	priv->byte0 = 0x8f;
	priv->mask0 = 0x8f;
	priv->flags = ALPS_DUALPOINT;

	priv->x_max = 2000;
	priv->y_max = 1400;

	switch (priv->proto_version) {
	case ALPS_PROTO_V1:
	case ALPS_PROTO_V2:
		priv->hw_init = alps_hw_init_v1_v2;
		priv->process_packet = alps_process_packet_v1_v2;
		priv->set_abs_params = alps_set_abs_params_st;
		break;
	case ALPS_PROTO_V3:
		priv->hw_init = alps_hw_init_v3;
		priv->process_packet = alps_process_packet_v3;
		priv->set_abs_params = alps_set_abs_params_mt;
		priv->decode_fields = alps_decode_pinnacle;
		priv->nibble_commands = alps_v3_nibble_commands;
		priv->addr_command = PSMOUSE_CMD_RESET_WRAP;
		break;
	case ALPS_PROTO_V4:
		priv->hw_init = alps_hw_init_v4;
		priv->process_packet = alps_process_packet_v4;
		priv->set_abs_params = alps_set_abs_params_mt;
		priv->nibble_commands = alps_v4_nibble_commands;
		priv->addr_command = PSMOUSE_CMD_DISABLE;
		break;
	case ALPS_PROTO_V5:
		priv->hw_init = alps_hw_init_dolphin_v1;
		priv->process_packet = alps_process_packet_v3;
		priv->decode_fields = alps_decode_dolphin;
		priv->set_abs_params = alps_set_abs_params_mt;
		priv->nibble_commands = alps_v3_nibble_commands;
		priv->addr_command = PSMOUSE_CMD_RESET_WRAP;
		priv->byte0 = 0xc8;
		priv->mask0 = 0xc8;
		priv->flags = 0;
		priv->x_max = 1360;
		priv->y_max = 660;
		break;
	}
}