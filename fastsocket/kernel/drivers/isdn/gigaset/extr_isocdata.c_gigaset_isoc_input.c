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
struct inbuf_t {unsigned int head; unsigned int tail; unsigned char* data; struct cardstate* cs; } ;
struct cardstate {scalar_t__ mstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  DEBUG_INTR ; 
 int /*<<< orphan*/  DEBUG_LOCKCMD ; 
 scalar_t__ MS_LOCKED ; 
 unsigned int RBUFSIZE ; 
 int /*<<< orphan*/  cmd_loop (unsigned char*,unsigned int,struct inbuf_t*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  gigaset_dbg_buffer (int /*<<< orphan*/ ,char*,unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  gigaset_if_receive (struct cardstate*,unsigned char*,unsigned int) ; 

void gigaset_isoc_input(struct inbuf_t *inbuf)
{
	struct cardstate *cs = inbuf->cs;
	unsigned tail, head, numbytes;
	unsigned char *src;

	head = inbuf->head;
	while (head != (tail = inbuf->tail)) {
		gig_dbg(DEBUG_INTR, "buffer state: %u -> %u", head, tail);
		if (head > tail)
			tail = RBUFSIZE;
		src = inbuf->data + head;
		numbytes = tail - head;
		gig_dbg(DEBUG_INTR, "processing %u bytes", numbytes);

		if (cs->mstate == MS_LOCKED) {
			gigaset_dbg_buffer(DEBUG_LOCKCMD, "received response",
					   numbytes, src);
			gigaset_if_receive(inbuf->cs, src, numbytes);
		} else {
			gigaset_dbg_buffer(DEBUG_CMD, "received response",
					   numbytes, src);
			cmd_loop(src, numbytes, inbuf);
		}

		head += numbytes;
		if (head == RBUFSIZE)
			head = 0;
		gig_dbg(DEBUG_INTR, "setting head to %u", head);
		inbuf->head = head;
	}
}