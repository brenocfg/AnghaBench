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
struct ldc_packet {scalar_t__ seqid; } ;
struct ldc_channel {int /*<<< orphan*/  rx_tail; scalar_t__ rcv_nxt; } ;

/* Variables and functions */
 int __set_rx_head (struct ldc_channel*,int /*<<< orphan*/ ) ; 
 int ldc_abort (struct ldc_channel*) ; 
 int send_data_nack (struct ldc_channel*,struct ldc_packet*) ; 

__attribute__((used)) static int rx_bad_seq(struct ldc_channel *lp, struct ldc_packet *p,
		      struct ldc_packet *first_frag)
{
	int err;

	if (first_frag)
		lp->rcv_nxt = first_frag->seqid - 1;

	err = send_data_nack(lp, p);
	if (err)
		return err;

	err = __set_rx_head(lp, lp->rx_tail);
	if (err < 0)
		return ldc_abort(lp);

	return 0;
}