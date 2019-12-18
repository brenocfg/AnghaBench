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
struct r3964_info {int state; int /*<<< orphan*/  rx_position; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAK ; 
 void* R3964_IDLE ; 
#define  R3964_RECEIVING 134 
#define  R3964_TX_REQUEST 133 
#define  R3964_WAIT_FOR_BCC 132 
#define  R3964_WAIT_FOR_RX_BUF 131 
#define  R3964_WAIT_FOR_RX_REPEAT 130 
#define  R3964_WAIT_FOR_TX_ACK 129 
#define  R3964_WAIT_ZVZ_BEFORE_TX_RETRY 128 
 int /*<<< orphan*/  TRACE_PE (char*,...) ; 
 int /*<<< orphan*/  flush (struct r3964_info*) ; 
 int /*<<< orphan*/  put_char (struct r3964_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retry_transmit (struct r3964_info*) ; 

__attribute__((used)) static void on_timeout(unsigned long priv)
{
	struct r3964_info *pInfo = (void *)priv;

	switch (pInfo->state) {
	case R3964_TX_REQUEST:
		TRACE_PE("TX_REQUEST - timeout");
		retry_transmit(pInfo);
		break;
	case R3964_WAIT_ZVZ_BEFORE_TX_RETRY:
		put_char(pInfo, NAK);
		flush(pInfo);
		retry_transmit(pInfo);
		break;
	case R3964_WAIT_FOR_TX_ACK:
		TRACE_PE("WAIT_FOR_TX_ACK - timeout");
		retry_transmit(pInfo);
		break;
	case R3964_WAIT_FOR_RX_BUF:
		TRACE_PE("WAIT_FOR_RX_BUF - timeout");
		put_char(pInfo, NAK);
		flush(pInfo);
		pInfo->state = R3964_IDLE;
		break;
	case R3964_RECEIVING:
		TRACE_PE("RECEIVING - timeout after %d chars",
			 pInfo->rx_position);
		put_char(pInfo, NAK);
		flush(pInfo);
		pInfo->state = R3964_IDLE;
		break;
	case R3964_WAIT_FOR_RX_REPEAT:
		TRACE_PE("WAIT_FOR_RX_REPEAT - timeout");
		pInfo->state = R3964_IDLE;
		break;
	case R3964_WAIT_FOR_BCC:
		TRACE_PE("WAIT_FOR_BCC - timeout");
		put_char(pInfo, NAK);
		flush(pInfo);
		pInfo->state = R3964_IDLE;
		break;
	}
}