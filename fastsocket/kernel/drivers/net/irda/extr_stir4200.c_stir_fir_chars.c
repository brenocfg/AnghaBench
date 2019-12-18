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
struct TYPE_6__ {int state; int* data; int* head; scalar_t__ len; scalar_t__ truesize; void* in_frame; } ;
struct stir_cb {TYPE_2__* netdev; TYPE_3__ rx_buff; } ;
typedef  TYPE_3__ iobuff_t ;
typedef  int __u8 ;
struct TYPE_4__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct TYPE_5__ {TYPE_1__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  BEGIN_FRAME 134 
 void* FALSE ; 
#define  FIR_CE 133 
#define  FIR_EOF 132 
#define  FIR_XBOF 131 
#define  INSIDE_FRAME 130 
 int IRDA_TRANS ; 
#define  LINK_ESCAPE 129 
#define  OUTSIDE_FRAME 128 
 void* TRUE ; 
 int /*<<< orphan*/  fir_eof (struct stir_cb*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void stir_fir_chars(struct stir_cb *stir,
			    const __u8 *bytes, int len)
{
	iobuff_t *rx_buff = &stir->rx_buff;
	int	i;

	for (i = 0; i < len; i++) {
		__u8	byte = bytes[i];

		switch(rx_buff->state) {
		case OUTSIDE_FRAME:
			/* ignore garbage till start of frame */
			if (unlikely(byte != FIR_EOF))
				continue;
			/* Now receiving frame */
			rx_buff->state = BEGIN_FRAME;

			/* Time to initialize receive buffer */
			rx_buff->data = rx_buff->head;
			rx_buff->len = 0;
			continue;

		case LINK_ESCAPE:
			if (byte == FIR_EOF) {
				pr_debug("%s: got EOF after escape\n",
					 stir->netdev->name);
				goto frame_error;
			}
			rx_buff->state = INSIDE_FRAME;
			byte ^= IRDA_TRANS;
			break;

		case BEGIN_FRAME:
			/* ignore multiple BOF/EOF */
			if (byte == FIR_EOF)
				continue;
			rx_buff->state = INSIDE_FRAME;
			rx_buff->in_frame = TRUE;

			/* fall through */
		case INSIDE_FRAME:
			switch(byte) {
			case FIR_CE:
				rx_buff->state = LINK_ESCAPE;
				continue;
			case FIR_XBOF:
				/* 0x7f is not used in this framing */
				pr_debug("%s: got XBOF without escape\n",
					 stir->netdev->name);
				goto frame_error;
			case FIR_EOF:
				rx_buff->state = OUTSIDE_FRAME;
				rx_buff->in_frame = FALSE;
				fir_eof(stir);
				continue;
			}
			break;
		}

		/* add byte to rx buffer */
		if (unlikely(rx_buff->len >= rx_buff->truesize)) {
			pr_debug("%s: fir frame exceeds %d\n",
				 stir->netdev->name, rx_buff->truesize);
			++stir->netdev->stats.rx_over_errors;
			goto error_recovery;
		}

		rx_buff->data[rx_buff->len++] = byte;
		continue;

	frame_error:
		++stir->netdev->stats.rx_frame_errors;

	error_recovery:
		++stir->netdev->stats.rx_errors;
		rx_buff->state = OUTSIDE_FRAME;
		rx_buff->in_frame = FALSE;
	}
}