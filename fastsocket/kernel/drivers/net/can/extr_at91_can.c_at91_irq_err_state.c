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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct can_frame {int /*<<< orphan*/  can_id; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int /*<<< orphan*/  bus_off; int /*<<< orphan*/  restarts; int /*<<< orphan*/  error_passive; int /*<<< orphan*/  error_warning; } ;
struct TYPE_6__ {int state; int /*<<< orphan*/  restart_ms; TYPE_2__ can_stats; } ;
struct at91_priv {TYPE_3__ can; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_ECR ; 
 int /*<<< orphan*/  AT91_IDR ; 
 int /*<<< orphan*/  AT91_IER ; 
 int AT91_IRQ_BOFF ; 
 int AT91_IRQ_ERRA ; 
 int AT91_IRQ_ERRP ; 
 int AT91_IRQ_WARN ; 
 int /*<<< orphan*/  CAN_ERR_BUSOFF ; 
 int /*<<< orphan*/  CAN_ERR_CRTL ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_RX_PASSIVE ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_RX_WARNING ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_TX_PASSIVE ; 
 int /*<<< orphan*/  CAN_ERR_CRTL_TX_WARNING ; 
 int /*<<< orphan*/  CAN_ERR_PROT ; 
 int /*<<< orphan*/  CAN_ERR_PROT_ACTIVE ; 
 int /*<<< orphan*/  CAN_ERR_RESTARTED ; 
#define  CAN_STATE_BUS_OFF 131 
#define  CAN_STATE_ERROR_ACTIVE 130 
#define  CAN_STATE_ERROR_PASSIVE 129 
#define  CAN_STATE_ERROR_WARNING 128 
 int /*<<< orphan*/  at91_chip_stop (struct net_device*,int const) ; 
 int at91_read (struct at91_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_write (struct at91_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct at91_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void at91_irq_err_state(struct net_device *dev,
		struct can_frame *cf, enum can_state new_state)
{
	struct at91_priv *priv = netdev_priv(dev);
	u32 reg_idr, reg_ier, reg_ecr;
	u8 tec, rec;

	reg_ecr = at91_read(priv, AT91_ECR);
	rec = reg_ecr & 0xff;
	tec = reg_ecr >> 16;

	switch (priv->can.state) {
	case CAN_STATE_ERROR_ACTIVE:
		/*
		 * from: ERROR_ACTIVE
		 * to  : ERROR_WARNING, ERROR_PASSIVE, BUS_OFF
		 * =>  : there was a warning int
		 */
		if (new_state >= CAN_STATE_ERROR_WARNING &&
		    new_state <= CAN_STATE_BUS_OFF) {
			dev_dbg(dev->dev.parent, "Error Warning IRQ\n");
			priv->can.can_stats.error_warning++;

			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] = (tec > rec) ?
				CAN_ERR_CRTL_TX_WARNING :
				CAN_ERR_CRTL_RX_WARNING;
		}
	case CAN_STATE_ERROR_WARNING:	/* fallthrough */
		/*
		 * from: ERROR_ACTIVE, ERROR_WARNING
		 * to  : ERROR_PASSIVE, BUS_OFF
		 * =>  : error passive int
		 */
		if (new_state >= CAN_STATE_ERROR_PASSIVE &&
		    new_state <= CAN_STATE_BUS_OFF) {
			dev_dbg(dev->dev.parent, "Error Passive IRQ\n");
			priv->can.can_stats.error_passive++;

			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] = (tec > rec) ?
				CAN_ERR_CRTL_TX_PASSIVE :
				CAN_ERR_CRTL_RX_PASSIVE;
		}
		break;
	case CAN_STATE_BUS_OFF:
		/*
		 * from: BUS_OFF
		 * to  : ERROR_ACTIVE, ERROR_WARNING, ERROR_PASSIVE
		 */
		if (new_state <= CAN_STATE_ERROR_PASSIVE) {
			cf->can_id |= CAN_ERR_RESTARTED;

			dev_dbg(dev->dev.parent, "restarted\n");
			priv->can.can_stats.restarts++;

			netif_carrier_on(dev);
			netif_wake_queue(dev);
		}
		break;
	default:
		break;
	}


	/* process state changes depending on the new state */
	switch (new_state) {
	case CAN_STATE_ERROR_ACTIVE:
		/*
		 * actually we want to enable AT91_IRQ_WARN here, but
		 * it screws up the system under certain
		 * circumstances. so just enable AT91_IRQ_ERRP, thus
		 * the "fallthrough"
		 */
		dev_dbg(dev->dev.parent, "Error Active\n");
		cf->can_id |= CAN_ERR_PROT;
		cf->data[2] = CAN_ERR_PROT_ACTIVE;
	case CAN_STATE_ERROR_WARNING:	/* fallthrough */
		reg_idr = AT91_IRQ_ERRA | AT91_IRQ_WARN | AT91_IRQ_BOFF;
		reg_ier = AT91_IRQ_ERRP;
		break;
	case CAN_STATE_ERROR_PASSIVE:
		reg_idr = AT91_IRQ_ERRA | AT91_IRQ_WARN | AT91_IRQ_ERRP;
		reg_ier = AT91_IRQ_BOFF;
		break;
	case CAN_STATE_BUS_OFF:
		reg_idr = AT91_IRQ_ERRA | AT91_IRQ_ERRP |
			AT91_IRQ_WARN | AT91_IRQ_BOFF;
		reg_ier = 0;

		cf->can_id |= CAN_ERR_BUSOFF;

		dev_dbg(dev->dev.parent, "bus-off\n");
		netif_carrier_off(dev);
		priv->can.can_stats.bus_off++;

		/* turn off chip, if restart is disabled */
		if (!priv->can.restart_ms) {
			at91_chip_stop(dev, CAN_STATE_BUS_OFF);
			return;
		}
		break;
	default:
		break;
	}

	at91_write(priv, AT91_IDR, reg_idr);
	at91_write(priv, AT91_IER, reg_ier);
}