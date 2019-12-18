#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct tty_struct {int dummy; } ;
struct TYPE_13__ {struct tty_struct* tty; } ;
struct TYPE_12__ {int clock_speed; } ;
struct TYPE_14__ {int tx_count; int tmp_rx_buf_count; TYPE_2__ port; TYPE_1__ params; int /*<<< orphan*/  lock; int /*<<< orphan*/  tmp_rx_buf; int /*<<< orphan*/  init_error; } ;
typedef  TYPE_3__ SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DiagStatus_DmaFailure ; 
 int TESTFRAMESIZE ; 
 int /*<<< orphan*/  enable_loopback (TYPE_3__*,int) ; 
 int /*<<< orphan*/  hdlc_mode (TYPE_3__*) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  reset_adapter (TYPE_3__*) ; 
 scalar_t__ rx_get_frame (TYPE_3__*) ; 
 int /*<<< orphan*/  rx_start (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_load_dma_buffer (TYPE_3__*,unsigned char*,int) ; 
 int /*<<< orphan*/  tx_start (TYPE_3__*) ; 

__attribute__((used)) static bool loopback_test(SLMP_INFO *info)
{
#define TESTFRAMESIZE 20

	unsigned long timeout;
	u16 count = TESTFRAMESIZE;
	unsigned char buf[TESTFRAMESIZE];
	bool rc = false;
	unsigned long flags;

	struct tty_struct *oldtty = info->port.tty;
	u32 speed = info->params.clock_speed;

	info->params.clock_speed = 3686400;
	info->port.tty = NULL;

	/* assume failure */
	info->init_error = DiagStatus_DmaFailure;

	/* build and send transmit frame */
	for (count = 0; count < TESTFRAMESIZE;++count)
		buf[count] = (unsigned char)count;

	memset(info->tmp_rx_buf,0,TESTFRAMESIZE);

	/* program hardware for HDLC and enabled receiver */
	spin_lock_irqsave(&info->lock,flags);
	hdlc_mode(info);
	enable_loopback(info,1);
       	rx_start(info);
	info->tx_count = count;
	tx_load_dma_buffer(info,buf,count);
	tx_start(info);
	spin_unlock_irqrestore(&info->lock,flags);

	/* wait for receive complete */
	/* Set a timeout for waiting for interrupt. */
	for ( timeout = 100; timeout; --timeout ) {
		msleep_interruptible(10);

		if (rx_get_frame(info)) {
			rc = true;
			break;
		}
	}

	/* verify received frame length and contents */
	if (rc &&
	    ( info->tmp_rx_buf_count != count ||
	      memcmp(buf, info->tmp_rx_buf,count))) {
		rc = false;
	}

	spin_lock_irqsave(&info->lock,flags);
	reset_adapter(info);
	spin_unlock_irqrestore(&info->lock,flags);

	info->params.clock_speed = speed;
	info->port.tty = oldtty;

	return rc;
}