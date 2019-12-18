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
struct TYPE_6__ {unsigned int ramsize; int /*<<< orphan*/  devicename; TYPE_1__* channel; } ;
struct TYPE_5__ {unsigned int buff_offset; unsigned int msg_len; } ;
struct TYPE_4__ {unsigned int first_sendbuf; unsigned int num_sendbufs; unsigned int free_sendbufs; unsigned int next_sendbuf; } ;
typedef  TYPE_2__ LLData ;

/* Variables and functions */
 unsigned int BUFFERS_MAX ; 
 unsigned int BUFFER_BASE ; 
 unsigned int BUFFER_SIZE ; 
 int /*<<< orphan*/  CEPID ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_VALID_CARD (int) ; 
 int /*<<< orphan*/  ceReqClass1 ; 
 int /*<<< orphan*/  ceReqLnkRead ; 
 int /*<<< orphan*/  ceReqTypeLnk ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 TYPE_3__** sc_adapter ; 
 int /*<<< orphan*/  sendmessage (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int*) ; 

int setup_buffers(int card, int c)
{
	unsigned int nBuffers, i, cBase;
	unsigned int buffer_size;
	LLData	RcvBuffOffset;

	if(!IS_VALID_CARD(card)) {
		pr_debug("invalid param: %d is not a valid card id\n", card);
		return -ENODEV;
	}

	/*
	 * Calculate the buffer offsets (send/recv/send/recv)
	 */
	pr_debug("%s: setting up channel buffer space in shared RAM\n",
			sc_adapter[card]->devicename);
	buffer_size = BUFFER_SIZE;
	nBuffers = ((sc_adapter[card]->ramsize - BUFFER_BASE) / buffer_size) / 2;
	nBuffers = nBuffers > BUFFERS_MAX ? BUFFERS_MAX : nBuffers;
	pr_debug("%s: calculating buffer space: %d buffers, %d big\n",
		sc_adapter[card]->devicename,
		nBuffers, buffer_size);
	if(nBuffers < 2) {
		pr_debug("%s: not enough buffer space\n",
			sc_adapter[card]->devicename);
		return -1;
	}
	cBase = (nBuffers * buffer_size) * (c - 1);
	pr_debug("%s: channel buffer offset from shared RAM: 0x%x\n",
			sc_adapter[card]->devicename, cBase);
	sc_adapter[card]->channel[c-1].first_sendbuf = BUFFER_BASE + cBase;
	sc_adapter[card]->channel[c-1].num_sendbufs = nBuffers / 2;
	sc_adapter[card]->channel[c-1].free_sendbufs = nBuffers / 2;
	sc_adapter[card]->channel[c-1].next_sendbuf = 0;
	pr_debug("%s: send buffer setup complete: first=0x%lx n=%d f=%d, nxt=%d\n",
				sc_adapter[card]->devicename,
				sc_adapter[card]->channel[c-1].first_sendbuf,
				sc_adapter[card]->channel[c-1].num_sendbufs,
				sc_adapter[card]->channel[c-1].free_sendbufs,
				sc_adapter[card]->channel[c-1].next_sendbuf);

	/*
	 * Prep the receive buffers
	 */
	pr_debug("%s: adding %d RecvBuffers:\n",
			sc_adapter[card]->devicename, nBuffers /2);
	for (i = 0 ; i < nBuffers / 2; i++) {
		RcvBuffOffset.buff_offset = 
			((sc_adapter[card]->channel[c-1].first_sendbuf +
			(nBuffers / 2) * buffer_size) + (buffer_size * i));
		RcvBuffOffset.msg_len = buffer_size;
		pr_debug("%s: adding RcvBuffer #%d offset=0x%lx sz=%d bufsz:%d\n",
				sc_adapter[card]->devicename,
				i + 1, RcvBuffOffset.buff_offset, 
				RcvBuffOffset.msg_len,buffer_size);
		sendmessage(card, CEPID, ceReqTypeLnk, ceReqClass1, ceReqLnkRead,
				c, sizeof(LLData), (unsigned int *)&RcvBuffOffset);
	} 
	return 0;
}