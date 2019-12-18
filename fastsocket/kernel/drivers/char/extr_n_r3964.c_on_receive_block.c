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
struct r3964_info {unsigned int rx_position; int flags; scalar_t__ bcc; scalar_t__ last_rx; scalar_t__ nRetry; void* state; int /*<<< orphan*/  read_wait; struct r3964_client_info* firstClient; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tmr; } ;
struct r3964_client_info {int sig_flags; struct r3964_client_info* next; } ;
struct r3964_block_header {unsigned int length; unsigned char* data; int /*<<< orphan*/ * owner; int /*<<< orphan*/ * next; scalar_t__ locks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAK ; 
 int R3964_BCC ; 
 int R3964_CHECKSUM ; 
 int R3964_ERROR ; 
 void* R3964_IDLE ; 
 scalar_t__ R3964_MAX_RETRIES ; 
 int /*<<< orphan*/  R3964_MSG_DATA ; 
 int /*<<< orphan*/  R3964_OK ; 
 int R3964_SIG_DATA ; 
 scalar_t__ R3964_TO_RX_PANIC ; 
 void* R3964_WAIT_FOR_RX_REPEAT ; 
 int /*<<< orphan*/  TRACE_M (char*,struct r3964_block_header*) ; 
 int /*<<< orphan*/  TRACE_PE (char*,...) ; 
 int /*<<< orphan*/  TRACE_PS (char*,unsigned int) ; 
 int /*<<< orphan*/  add_msg (struct r3964_client_info*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct r3964_block_header*) ; 
 int /*<<< orphan*/  add_rx_queue (struct r3964_info*,struct r3964_block_header*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush (struct r3964_info*) ; 
 scalar_t__ jiffies ; 
 struct r3964_block_header* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  put_char (struct r3964_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trigger_transmit (struct r3964_info*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_receive_block(struct r3964_info *pInfo)
{
	unsigned int length;
	struct r3964_client_info *pClient;
	struct r3964_block_header *pBlock;

	length = pInfo->rx_position;

	/* compare byte checksum characters: */
	if (pInfo->flags & R3964_BCC) {
		if (pInfo->bcc != pInfo->last_rx) {
			TRACE_PE("checksum error - got %x but expected %x",
				 pInfo->last_rx, pInfo->bcc);
			pInfo->flags |= R3964_CHECKSUM;
		}
	}

	/* check for errors (parity, overrun,...): */
	if (pInfo->flags & R3964_ERROR) {
		TRACE_PE("on_receive_block - transmission failed error %x",
			 pInfo->flags & R3964_ERROR);

		put_char(pInfo, NAK);
		flush(pInfo);
		if (pInfo->nRetry < R3964_MAX_RETRIES) {
			pInfo->state = R3964_WAIT_FOR_RX_REPEAT;
			pInfo->nRetry++;
			mod_timer(&pInfo->tmr, jiffies + R3964_TO_RX_PANIC);
		} else {
			TRACE_PE("on_receive_block - failed after max retries");
			pInfo->state = R3964_IDLE;
		}
		return;
	}

	/* received block; submit DLE: */
	put_char(pInfo, DLE);
	flush(pInfo);
	del_timer_sync(&pInfo->tmr);
	TRACE_PS(" rx success: got %d chars", length);

	/* prepare struct r3964_block_header: */
	pBlock = kmalloc(length + sizeof(struct r3964_block_header),
			GFP_KERNEL);
	TRACE_M("on_receive_block - kmalloc %p", pBlock);

	if (pBlock == NULL)
		return;

	pBlock->length = length;
	pBlock->data = ((unsigned char *)pBlock) +
			sizeof(struct r3964_block_header);
	pBlock->locks = 0;
	pBlock->next = NULL;
	pBlock->owner = NULL;

	memcpy(pBlock->data, pInfo->rx_buf, length);

	/* queue block into rx_queue: */
	add_rx_queue(pInfo, pBlock);

	/* notify attached client processes: */
	for (pClient = pInfo->firstClient; pClient; pClient = pClient->next) {
		if (pClient->sig_flags & R3964_SIG_DATA) {
			add_msg(pClient, R3964_MSG_DATA, length, R3964_OK,
				pBlock);
		}
	}
	wake_up_interruptible(&pInfo->read_wait);

	pInfo->state = R3964_IDLE;

	trigger_transmit(pInfo);
}