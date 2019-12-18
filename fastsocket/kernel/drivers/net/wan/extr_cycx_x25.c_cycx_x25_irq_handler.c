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
typedef  int /*<<< orphan*/  z ;
typedef  int /*<<< orphan*/  u16 ;
struct cycx_x25_cmd {int command; } ;
struct cycx_device {int in_isr; int /*<<< orphan*/  hw; scalar_t__ buff_int_mode_unbusy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  WAN_CONNECTED ; 
 int /*<<< orphan*/  WAN_DISCONNECTED ; 
#define  X25_ACK_FROM_VC 137 
#define  X25_CONNECT_CONFIRM 136 
#define  X25_CONNECT_INDICATION 135 
#define  X25_DATA_INDICATION 134 
#define  X25_DISCONNECT_CONFIRM 133 
#define  X25_DISCONNECT_INDICATION 132 
#define  X25_LINE_OFF 131 
#define  X25_LINE_ON 130 
#define  X25_LOG 129 
 int /*<<< orphan*/  X25_RXMBOX_OFFS ; 
#define  X25_STATISTIC 128 
 int /*<<< orphan*/  cycx_peek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cycx_x25_cmd*,int) ; 
 int /*<<< orphan*/  cycx_poke (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cycx_set_state (struct cycx_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cycx_x25_irq_connect (struct cycx_device*,struct cycx_x25_cmd*) ; 
 int /*<<< orphan*/  cycx_x25_irq_connect_confirm (struct cycx_device*,struct cycx_x25_cmd*) ; 
 int /*<<< orphan*/  cycx_x25_irq_disconnect (struct cycx_device*,struct cycx_x25_cmd*) ; 
 int /*<<< orphan*/  cycx_x25_irq_disconnect_confirm (struct cycx_device*,struct cycx_x25_cmd*) ; 
 int /*<<< orphan*/  cycx_x25_irq_log (struct cycx_device*,struct cycx_x25_cmd*) ; 
 int /*<<< orphan*/  cycx_x25_irq_rx (struct cycx_device*,struct cycx_x25_cmd*) ; 
 int /*<<< orphan*/  cycx_x25_irq_spurious (struct cycx_device*,struct cycx_x25_cmd*) ; 
 int /*<<< orphan*/  cycx_x25_irq_stat (struct cycx_device*,struct cycx_x25_cmd*) ; 
 int /*<<< orphan*/  cycx_x25_irq_tx (struct cycx_device*,struct cycx_x25_cmd*) ; 

__attribute__((used)) static void cycx_x25_irq_handler(struct cycx_device *card)
{
	struct cycx_x25_cmd cmd;
	u16 z = 0;

	card->in_isr = 1;
	card->buff_int_mode_unbusy = 0;
	cycx_peek(&card->hw, X25_RXMBOX_OFFS, &cmd, sizeof(cmd));

	switch (cmd.command) {
	case X25_DATA_INDICATION:
		cycx_x25_irq_rx(card, &cmd);
		break;
	case X25_ACK_FROM_VC:
		cycx_x25_irq_tx(card, &cmd);
		break;
	case X25_LOG:
		cycx_x25_irq_log(card, &cmd);
		break;
	case X25_STATISTIC:
		cycx_x25_irq_stat(card, &cmd);
		break;
	case X25_CONNECT_CONFIRM:
		cycx_x25_irq_connect_confirm(card, &cmd);
		break;
	case X25_CONNECT_INDICATION:
		cycx_x25_irq_connect(card, &cmd);
		break;
	case X25_DISCONNECT_INDICATION:
		cycx_x25_irq_disconnect(card, &cmd);
		break;
	case X25_DISCONNECT_CONFIRM:
		cycx_x25_irq_disconnect_confirm(card, &cmd);
		break;
	case X25_LINE_ON:
		cycx_set_state(card, WAN_CONNECTED);
		break;
	case X25_LINE_OFF:
		cycx_set_state(card, WAN_DISCONNECTED);
		break;
	default:
		cycx_x25_irq_spurious(card, &cmd);
		break;
	}

	cycx_poke(&card->hw, 0, &z, sizeof(z));
	cycx_poke(&card->hw, X25_RXMBOX_OFFS, &z, sizeof(z));
	card->in_isr = 0;
}