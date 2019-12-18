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
struct r3964_info {scalar_t__ nRetry; int /*<<< orphan*/  state; int /*<<< orphan*/  tmr; scalar_t__ bcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAK ; 
 int /*<<< orphan*/  R3964_IDLE ; 
 scalar_t__ R3964_MAX_RETRIES ; 
 scalar_t__ R3964_TO_QVZ ; 
 int /*<<< orphan*/  R3964_TX_FAIL ; 
 int /*<<< orphan*/  R3964_TX_REQUEST ; 
 int /*<<< orphan*/  STX ; 
 int /*<<< orphan*/  TRACE_PE (char*,scalar_t__) ; 
 int /*<<< orphan*/  flush (struct r3964_info*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  put_char (struct r3964_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_from_tx_queue (struct r3964_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trigger_transmit (struct r3964_info*) ; 

__attribute__((used)) static void retry_transmit(struct r3964_info *pInfo)
{
	if (pInfo->nRetry < R3964_MAX_RETRIES) {
		TRACE_PE("transmission failed. Retry #%d", pInfo->nRetry);
		pInfo->bcc = 0;
		put_char(pInfo, STX);
		flush(pInfo);
		pInfo->state = R3964_TX_REQUEST;
		pInfo->nRetry++;
		mod_timer(&pInfo->tmr, jiffies + R3964_TO_QVZ);
	} else {
		TRACE_PE("transmission failed after %d retries",
			 R3964_MAX_RETRIES);

		remove_from_tx_queue(pInfo, R3964_TX_FAIL);

		put_char(pInfo, NAK);
		flush(pInfo);
		pInfo->state = R3964_IDLE;

		trigger_transmit(pInfo);
	}
}