#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* i2ChanStrPtr ;
struct TYPE_7__ {TYPE_1__* driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  Pbuf_spinlock; } ;
typedef  TYPE_2__* PTTY ;

/* Variables and functions */
 int /*<<< orphan*/  CHANN ; 
 int /*<<< orphan*/  ITRC_ENTER ; 
 int /*<<< orphan*/  ITRC_RETURN ; 
 int /*<<< orphan*/  ITRC_WRITE ; 
 int i2Output (TYPE_1__*,unsigned char const*,int) ; 
 int /*<<< orphan*/  ip2_flush_chars (TYPE_2__*) ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
ip2_write( PTTY tty, const unsigned char *pData, int count)
{
	i2ChanStrPtr  pCh = tty->driver_data;
	int bytesSent = 0;
	unsigned long flags;

	ip2trace (CHANN, ITRC_WRITE, ITRC_ENTER, 2, count, -1 );

	/* Flush out any buffered data left over from ip2_putchar() calls. */
	ip2_flush_chars( tty );

	/* This is the actual move bit. Make sure it does what we need!!!!! */
	write_lock_irqsave(&pCh->Pbuf_spinlock, flags);
	bytesSent = i2Output( pCh, pData, count);
	write_unlock_irqrestore(&pCh->Pbuf_spinlock, flags);

	ip2trace (CHANN, ITRC_WRITE, ITRC_RETURN, 1, bytesSent );

	return bytesSent > 0 ? bytesSent : 0;
}