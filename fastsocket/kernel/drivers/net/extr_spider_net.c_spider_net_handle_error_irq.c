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
typedef  int u32 ;
struct spider_net_card {int ignore_rx_ramfull; TYPE_1__* netdev; int /*<<< orphan*/  napi; int /*<<< orphan*/  num_rx_ints; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  SPIDER_NET_GDADCEINT 158 
#define  SPIDER_NET_GDADEN0INT 157 
#define  SPIDER_NET_GDAFDCINT 156 
#define  SPIDER_NET_GDAINVDINT 155 
#define  SPIDER_NET_GDBDCEINT 154 
#define  SPIDER_NET_GDBDEN0INT 153 
#define  SPIDER_NET_GDBFDCINT 152 
#define  SPIDER_NET_GDBINVDINT 151 
#define  SPIDER_NET_GDCDCEINT 150 
#define  SPIDER_NET_GDCDEN0INT 149 
#define  SPIDER_NET_GDCFDCINT 148 
#define  SPIDER_NET_GDCINVDINT 147 
#define  SPIDER_NET_GDDDCEINT 146 
#define  SPIDER_NET_GDDDEN0INT 145 
#define  SPIDER_NET_GDDFDCINT 144 
#define  SPIDER_NET_GDDINVDINT 143 
#define  SPIDER_NET_GDTDCEINT 142 
#define  SPIDER_NET_GDTDEN0INT 141 
#define  SPIDER_NET_GDTFDCINT 140 
#define  SPIDER_NET_GDTINVDINT 139 
 int /*<<< orphan*/  SPIDER_NET_GHIINT1STS ; 
 int /*<<< orphan*/  SPIDER_NET_GHIINT2STS ; 
#define  SPIDER_NET_GIPSINT 138 
#define  SPIDER_NET_GPROPCMPINT 137 
#define  SPIDER_NET_GPWFFINT 136 
#define  SPIDER_NET_GPWOPCMPINT 135 
#define  SPIDER_NET_GRFAFLLINT 134 
#define  SPIDER_NET_GRFBFLLINT 133 
#define  SPIDER_NET_GRFCFLLINT 132 
#define  SPIDER_NET_GRFDFLLINT 131 
#define  SPIDER_NET_GRMFLLINT 130 
#define  SPIDER_NET_GTMFLLINT 129 
#define  SPIDER_NET_GTTEDINT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ net_ratelimit () ; 
 scalar_t__ netif_msg_intr (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_enable_rxdmac (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_refill_rx_chain (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_resync_head_ptr (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
spider_net_handle_error_irq(struct spider_net_card *card, u32 status_reg,
			    u32 error_reg1, u32 error_reg2)
{
	u32 i;
	int show_error = 1;

	/* check GHIINT0STS ************************************/
	if (status_reg)
		for (i = 0; i < 32; i++)
			if (status_reg & (1<<i))
				switch (i)
	{
	/* let error_reg1 and error_reg2 evaluation decide, what to do
	case SPIDER_NET_PHYINT:
	case SPIDER_NET_GMAC2INT:
	case SPIDER_NET_GMAC1INT:
	case SPIDER_NET_GFIFOINT:
	case SPIDER_NET_DMACINT:
	case SPIDER_NET_GSYSINT:
		break; */

	case SPIDER_NET_GIPSINT:
		show_error = 0;
		break;

	case SPIDER_NET_GPWOPCMPINT:
		/* PHY write operation completed */
		show_error = 0;
		break;
	case SPIDER_NET_GPROPCMPINT:
		/* PHY read operation completed */
		/* we don't use semaphores, as we poll for the completion
		 * of the read operation in spider_net_read_phy. Should take
		 * about 50 us */
		show_error = 0;
		break;
	case SPIDER_NET_GPWFFINT:
		/* PHY command queue full */
		if (netif_msg_intr(card))
			dev_err(&card->netdev->dev, "PHY write queue full\n");
		show_error = 0;
		break;

	/* case SPIDER_NET_GRMDADRINT: not used. print a message */
	/* case SPIDER_NET_GRMARPINT: not used. print a message */
	/* case SPIDER_NET_GRMMPINT: not used. print a message */

	case SPIDER_NET_GDTDEN0INT:
		/* someone has set TX_DMA_EN to 0 */
		show_error = 0;
		break;

	case SPIDER_NET_GDDDEN0INT: /* fallthrough */
	case SPIDER_NET_GDCDEN0INT: /* fallthrough */
	case SPIDER_NET_GDBDEN0INT: /* fallthrough */
	case SPIDER_NET_GDADEN0INT:
		/* someone has set RX_DMA_EN to 0 */
		show_error = 0;
		break;

	/* RX interrupts */
	case SPIDER_NET_GDDFDCINT:
	case SPIDER_NET_GDCFDCINT:
	case SPIDER_NET_GDBFDCINT:
	case SPIDER_NET_GDAFDCINT:
	/* case SPIDER_NET_GDNMINT: not used. print a message */
	/* case SPIDER_NET_GCNMINT: not used. print a message */
	/* case SPIDER_NET_GBNMINT: not used. print a message */
	/* case SPIDER_NET_GANMINT: not used. print a message */
	/* case SPIDER_NET_GRFNMINT: not used. print a message */
		show_error = 0;
		break;

	/* TX interrupts */
	case SPIDER_NET_GDTFDCINT:
		show_error = 0;
		break;
	case SPIDER_NET_GTTEDINT:
		show_error = 0;
		break;
	case SPIDER_NET_GDTDCEINT:
		/* chain end. If a descriptor should be sent, kick off
		 * tx dma
		if (card->tx_chain.tail != card->tx_chain.head)
			spider_net_kick_tx_dma(card);
		*/
		show_error = 0;
		break;

	/* case SPIDER_NET_G1TMCNTINT: not used. print a message */
	/* case SPIDER_NET_GFREECNTINT: not used. print a message */
	}

	/* check GHIINT1STS ************************************/
	if (error_reg1)
		for (i = 0; i < 32; i++)
			if (error_reg1 & (1<<i))
				switch (i)
	{
	case SPIDER_NET_GTMFLLINT:
		/* TX RAM full may happen on a usual case.
		 * Logging is not needed. */
		show_error = 0;
		break;
	case SPIDER_NET_GRFDFLLINT: /* fallthrough */
	case SPIDER_NET_GRFCFLLINT: /* fallthrough */
	case SPIDER_NET_GRFBFLLINT: /* fallthrough */
	case SPIDER_NET_GRFAFLLINT: /* fallthrough */
	case SPIDER_NET_GRMFLLINT:
		/* Could happen when rx chain is full */
		if (card->ignore_rx_ramfull == 0) {
			card->ignore_rx_ramfull = 1;
			spider_net_resync_head_ptr(card);
			spider_net_refill_rx_chain(card);
			spider_net_enable_rxdmac(card);
			card->num_rx_ints ++;
			napi_schedule(&card->napi);
		}
		show_error = 0;
		break;

	/* case SPIDER_NET_GTMSHTINT: problem, print a message */
	case SPIDER_NET_GDTINVDINT:
		/* allrighty. tx from previous descr ok */
		show_error = 0;
		break;

	/* chain end */
	case SPIDER_NET_GDDDCEINT: /* fallthrough */
	case SPIDER_NET_GDCDCEINT: /* fallthrough */
	case SPIDER_NET_GDBDCEINT: /* fallthrough */
	case SPIDER_NET_GDADCEINT:
		spider_net_resync_head_ptr(card);
		spider_net_refill_rx_chain(card);
		spider_net_enable_rxdmac(card);
		card->num_rx_ints ++;
		napi_schedule(&card->napi);
		show_error = 0;
		break;

	/* invalid descriptor */
	case SPIDER_NET_GDDINVDINT: /* fallthrough */
	case SPIDER_NET_GDCINVDINT: /* fallthrough */
	case SPIDER_NET_GDBINVDINT: /* fallthrough */
	case SPIDER_NET_GDAINVDINT:
		/* Could happen when rx chain is full */
		spider_net_resync_head_ptr(card);
		spider_net_refill_rx_chain(card);
		spider_net_enable_rxdmac(card);
		card->num_rx_ints ++;
		napi_schedule(&card->napi);
		show_error = 0;
		break;

	/* case SPIDER_NET_GDTRSERINT: problem, print a message */
	/* case SPIDER_NET_GDDRSERINT: problem, print a message */
	/* case SPIDER_NET_GDCRSERINT: problem, print a message */
	/* case SPIDER_NET_GDBRSERINT: problem, print a message */
	/* case SPIDER_NET_GDARSERINT: problem, print a message */
	/* case SPIDER_NET_GDSERINT: problem, print a message */
	/* case SPIDER_NET_GDTPTERINT: problem, print a message */
	/* case SPIDER_NET_GDDPTERINT: problem, print a message */
	/* case SPIDER_NET_GDCPTERINT: problem, print a message */
	/* case SPIDER_NET_GDBPTERINT: problem, print a message */
	/* case SPIDER_NET_GDAPTERINT: problem, print a message */
	default:
		show_error = 1;
		break;
	}

	/* check GHIINT2STS ************************************/
	if (error_reg2)
		for (i = 0; i < 32; i++)
			if (error_reg2 & (1<<i))
				switch (i)
	{
	/* there is nothing we can (want  to) do at this time. Log a
	 * message, we can switch on and off the specific values later on
	case SPIDER_NET_GPROPERINT:
	case SPIDER_NET_GMCTCRSNGINT:
	case SPIDER_NET_GMCTLCOLINT:
	case SPIDER_NET_GMCTTMOTINT:
	case SPIDER_NET_GMCRCAERINT:
	case SPIDER_NET_GMCRCALERINT:
	case SPIDER_NET_GMCRALNERINT:
	case SPIDER_NET_GMCROVRINT:
	case SPIDER_NET_GMCRRNTINT:
	case SPIDER_NET_GMCRRXERINT:
	case SPIDER_NET_GTITCSERINT:
	case SPIDER_NET_GTIFMTERINT:
	case SPIDER_NET_GTIPKTRVKINT:
	case SPIDER_NET_GTISPINGINT:
	case SPIDER_NET_GTISADNGINT:
	case SPIDER_NET_GTISPDNGINT:
	case SPIDER_NET_GRIFMTERINT:
	case SPIDER_NET_GRIPKTRVKINT:
	case SPIDER_NET_GRISPINGINT:
	case SPIDER_NET_GRISADNGINT:
	case SPIDER_NET_GRISPDNGINT:
		break;
	*/
		default:
			break;
	}

	if ((show_error) && (netif_msg_intr(card)) && net_ratelimit())
		dev_err(&card->netdev->dev, "Error interrupt, GHIINT0STS = 0x%08x, "
		       "GHIINT1STS = 0x%08x, GHIINT2STS = 0x%08x\n",
		       status_reg, error_reg1, error_reg2);

	/* clear interrupt sources */
	spider_net_write_reg(card, SPIDER_NET_GHIINT1STS, error_reg1);
	spider_net_write_reg(card, SPIDER_NET_GHIINT2STS, error_reg2);
}