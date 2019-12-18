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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * rxcmdpkt; } ;
struct r8192_priv {TYPE_1__ stats; } ;
struct net_device {int dummy; } ;
struct ieee80211_rx_stats {int Length; int* virtual_address; } ;
typedef  int /*<<< orphan*/  cmpk_intr_sta_t ;

/* Variables and functions */
#define  BOTH_QUERY_CONFIG 133 
 int CMPK_BOTH_QUERY_CONFIG_SIZE ; 
 int CMPK_RX_TX_FB_SIZE ; 
 int CMPK_RX_TX_STS_SIZE ; 
 int CMPK_TX_RAHIS_SIZE ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
#define  RX_INTERRUPT_STATUS 132 
#define  RX_TX_FEEDBACK 131 
#define  RX_TX_PER_PKT_FEEDBACK 130 
#define  RX_TX_RATE_HISTORY 129 
#define  RX_TX_STATUS 128 
 int /*<<< orphan*/  cmpk_handle_interrupt_status (struct net_device*,int*) ; 
 int /*<<< orphan*/  cmpk_handle_query_config_rx (struct net_device*,int*) ; 
 int /*<<< orphan*/  cmpk_handle_tx_feedback (struct net_device*,int*) ; 
 int /*<<< orphan*/  cmpk_handle_tx_rate_history (struct net_device*,int*) ; 
 int /*<<< orphan*/  cmpk_handle_tx_status (struct net_device*,int*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

extern	u32
cmpk_message_handle_rx(
	struct net_device *dev,
	struct ieee80211_rx_stats *pstats)
{
//	u32			debug_level = DBG_LOUD;
	struct r8192_priv *priv = ieee80211_priv(dev);
	int			total_length;
	u8			cmd_length, exe_cnt = 0;
	u8			element_id;
	u8			*pcmd_buff;

	/* 0. Check inpt arguments. If is is a command queue message or pointer is
	      null. */
	if (/*(prfd->queue_id != CMPK_RX_QUEUE_ID) || */(pstats== NULL))
	{
		/* Print error message. */
		/*RT_TRACE(COMP_SEND, DebugLevel,
				("\n\r[CMPK]-->Err queue id or pointer"));*/
		return 0;	/* This is not a command packet. */
	}

	/* 1. Read received command packet message length from RFD. */
	total_length = pstats->Length;

	/* 2. Read virtual address from RFD. */
	pcmd_buff = pstats->virtual_address;

	/* 3. Read command pakcet element id and length. */
	element_id = pcmd_buff[0];
	/*RT_TRACE(COMP_SEND, DebugLevel,
			("\n\r[CMPK]-->element ID=%d Len=%d", element_id, total_length));*/

	/* 4. Check every received command packet conent according to different
	      element type. Because FW may aggregate RX command packet to minimize
	      transmit time between DRV and FW.*/
	// Add a counter to prevent to locked in the loop too long
	while (total_length > 0 || exe_cnt++ >100)
	{
		/* 2007/01/17 MH We support aggregation of different cmd in the same packet. */
		element_id = pcmd_buff[0];

		switch(element_id)
		{
			case RX_TX_FEEDBACK:
				cmpk_handle_tx_feedback (dev, pcmd_buff);
				cmd_length = CMPK_RX_TX_FB_SIZE;
				break;

			case RX_INTERRUPT_STATUS:
				cmpk_handle_interrupt_status(dev, pcmd_buff);
				cmd_length = sizeof(cmpk_intr_sta_t);
				break;

			case BOTH_QUERY_CONFIG:
				cmpk_handle_query_config_rx(dev, pcmd_buff);
				cmd_length = CMPK_BOTH_QUERY_CONFIG_SIZE;
				break;

			case RX_TX_STATUS:
				cmpk_handle_tx_status(dev, pcmd_buff);
				cmd_length = CMPK_RX_TX_STS_SIZE;
				break;

			case RX_TX_PER_PKT_FEEDBACK:
				// You must at lease add a switch case element here,
				// Otherwise, we will jump to default case.
				//DbgPrint("CCX Test\r\n");
				cmd_length = CMPK_RX_TX_FB_SIZE;
				break;

			case RX_TX_RATE_HISTORY:
				//DbgPrint(" rx tx rate history\r\n");
				cmpk_handle_tx_rate_history(dev, pcmd_buff);
				cmd_length = CMPK_TX_RAHIS_SIZE;
				break;

			default:

			        RT_TRACE(COMP_ERR, "---->cmpk_message_handle_rx():unknow CMD Element\n");
				return 1;	/* This is a command packet. */
		}
		// 2007/01/22 MH Display received rx command packet info.
		//cmpk_Display_Message(cmd_length, pcmd_buff);

		// 2007/01/22 MH Add to display tx statistic.
		//cmpk_DisplayTxStatistic(pAdapter);

		/* 2007/03/09 MH Collect sidderent cmd element pkt num. */
		priv->stats.rxcmdpkt[element_id]++;

		total_length -= cmd_length;
		pcmd_buff    += cmd_length;
	}	/* while (total_length > 0) */
	return	1;	/* This is a command packet. */

}