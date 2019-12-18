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
struct cx88_dmaqueue {int /*<<< orphan*/  timeout; } ;
struct cx8802_dev {struct cx88_dmaqueue mpegq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx8802_stop_dma (struct cx8802_dev*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_cancel_buffers (struct cx8802_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

void cx8802_cancel_buffers(struct cx8802_dev *dev)
{
	struct cx88_dmaqueue *q = &dev->mpegq;

	dprintk( 1, "cx8802_cancel_buffers" );
	del_timer_sync(&q->timeout);
	cx8802_stop_dma(dev);
	do_cancel_buffers(dev,"cancel",0);
}