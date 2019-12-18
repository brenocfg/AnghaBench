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
struct isowbuf_t {int write; int idle; int* data; int wbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ISO ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  isowbuf_putbits (struct isowbuf_t*,int,int) ; 

__attribute__((used)) static inline void isowbuf_putflag(struct isowbuf_t *iwb)
{
	int write;

	/* add two flags, thus reliably covering one byte */
	isowbuf_putbits(iwb, 0x7e7e, 8);
	/* recover the idle flag byte */
	write = iwb->write;
	iwb->idle = iwb->data[write];
	gig_dbg(DEBUG_ISO, "idle fill byte %02x", iwb->idle);
	/* mask extraneous bits in buffer */
	iwb->data[write] &= (1 << iwb->wbits) - 1;
}