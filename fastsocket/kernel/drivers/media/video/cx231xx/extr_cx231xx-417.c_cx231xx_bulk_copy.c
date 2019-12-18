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
typedef  int u32 ;
struct urb {unsigned char* transfer_buffer; int actual_length; struct cx231xx_dmaqueue* context; } ;
struct cx231xx_dmaqueue {unsigned char* ps_head; } ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  buffer_filled (unsigned char*,int,struct urb*,struct cx231xx_dmaqueue*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static inline int cx231xx_bulk_copy(struct cx231xx *dev, struct urb *urb)
{

	/*char *outp;*/
	/*struct cx231xx_buffer *buf;*/
	struct cx231xx_dmaqueue *dma_q = urb->context;
	unsigned char *p_buffer, *buffer;
	u32 buffer_size = 0;

	p_buffer = urb->transfer_buffer;
	buffer_size = urb->actual_length;

	buffer = kmalloc(buffer_size, GFP_ATOMIC);

	memcpy(buffer, dma_q->ps_head, 3);
	memcpy(buffer+3, p_buffer, buffer_size-3);
	memcpy(dma_q->ps_head, p_buffer+buffer_size-3, 3);

	p_buffer = buffer;
	buffer_filled(p_buffer, buffer_size, urb, dma_q);

	kfree(buffer);
	return 0;
}