#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned short len; } ;
struct TYPE_7__ {int net_tx_busy; unsigned short async_len; unsigned short async_channel; scalar_t__ err_log_state; int myid; scalar_t__ async_busy; int /*<<< orphan*/  async_data; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 unsigned short CHAN_CAPI ; 
 unsigned short CHAN_ERRLOG ; 
 unsigned short CHAN_NDIS_DATA ; 
 int /*<<< orphan*/  ERRLOG_CMD_REQ ; 
 unsigned short ERRLOG_CMD_REQ_SIZE ; 
 int /*<<< orphan*/  ERRLOG_CMD_STOP ; 
 unsigned short ERRLOG_CMD_STOP_SIZE ; 
 scalar_t__ ERRLOG_STATE_OFF ; 
 scalar_t__ ERRLOG_STATE_ON ; 
 scalar_t__ ERRLOG_STATE_START ; 
 scalar_t__ ERRLOG_STATE_STOP ; 
 int hycapi_enable ; 
 int /*<<< orphan*/  hycapi_tx_capiack (TYPE_1__*) ; 
 struct sk_buff* hycapi_tx_capiget (TYPE_1__*) ; 
 int hynet_enable ; 
 int /*<<< orphan*/  hysdn_tx_netack (TYPE_1__*) ; 
 struct sk_buff* hysdn_tx_netget (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,unsigned char*,unsigned short) ; 
 int /*<<< orphan*/  strcpy (unsigned char*,int /*<<< orphan*/ ) ; 

int
hysdn_sched_tx(hysdn_card *card, unsigned char *buf,
		unsigned short volatile *len, unsigned short volatile *chan,
		unsigned short maxlen)
{
	struct sk_buff *skb;

	if (card->net_tx_busy) {
		card->net_tx_busy = 0;	/* reset flag */
		hysdn_tx_netack(card);	/* acknowledge packet send */
	}			/* a network packet has completely been transferred */
	/* first of all async requests are handled */
	if (card->async_busy) {
		if (card->async_len <= maxlen) {
			memcpy(buf, card->async_data, card->async_len);
			*len = card->async_len;
			*chan = card->async_channel;
			card->async_busy = 0;	/* reset request */
			return (1);
		}
		card->async_busy = 0;	/* in case of length error */
	}			/* async request */
	if ((card->err_log_state == ERRLOG_STATE_START) &&
	    (maxlen >= ERRLOG_CMD_REQ_SIZE)) {
		strcpy(buf, ERRLOG_CMD_REQ);	/* copy the command */
		*len = ERRLOG_CMD_REQ_SIZE;	/* buffer length */
		*chan = CHAN_ERRLOG;	/* and channel */
		card->err_log_state = ERRLOG_STATE_ON;	/* new state is on */
		return (1);	/* tell that data should be send */
	}			/* error log start and able to send */
	if ((card->err_log_state == ERRLOG_STATE_STOP) &&
	    (maxlen >= ERRLOG_CMD_STOP_SIZE)) {
		strcpy(buf, ERRLOG_CMD_STOP);	/* copy the command */
		*len = ERRLOG_CMD_STOP_SIZE;	/* buffer length */
		*chan = CHAN_ERRLOG;	/* and channel */
		card->err_log_state = ERRLOG_STATE_OFF;		/* new state is off */
		return (1);	/* tell that data should be send */
	}			/* error log start and able to send */
	/* now handle network interface packets */
	if ((hynet_enable & (1 << card->myid)) && 
	    (skb = hysdn_tx_netget(card)) != NULL) 
	{
		if (skb->len <= maxlen) {
			/* copy the packet to the buffer */
			skb_copy_from_linear_data(skb, buf, skb->len);
			*len = skb->len;
			*chan = CHAN_NDIS_DATA;
			card->net_tx_busy = 1;	/* we are busy sending network data */
			return (1);	/* go and send the data */
		} else
			hysdn_tx_netack(card);	/* aknowledge packet -> throw away */
	}			/* send a network packet if available */
#ifdef CONFIG_HYSDN_CAPI
	if( ((hycapi_enable & (1 << card->myid))) && 
	    ((skb = hycapi_tx_capiget(card)) != NULL) )
	{
		if (skb->len <= maxlen) {
			skb_copy_from_linear_data(skb, buf, skb->len);
			*len = skb->len;
			*chan = CHAN_CAPI;
			hycapi_tx_capiack(card);
			return (1);	/* go and send the data */
		}
	}
#endif /* CONFIG_HYSDN_CAPI */
	return (0);		/* nothing to send */
}