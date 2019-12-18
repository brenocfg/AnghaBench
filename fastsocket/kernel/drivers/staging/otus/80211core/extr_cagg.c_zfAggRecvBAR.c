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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,int) ; 
 int /*<<< orphan*/  zfSendBA (int /*<<< orphan*/ *,int,int*) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfAggRecvBAR(zdev_t* dev, zbuf_t *buf) {
    u16_t start_seq, len;
    u8_t i, bitmap[8];
    len = zfwBufGetSize(dev, buf);
    start_seq = zmw_rx_buf_readh(dev, buf, len-2);
    DbgPrint("Received a BAR Control frame, start_seq=%d", start_seq>>4);
    /* todo: set the bitmap by reordering buffer! */
    for (i=0; i<8; i++) bitmap[i]=0;
    zfSendBA(dev, start_seq, bitmap);
}