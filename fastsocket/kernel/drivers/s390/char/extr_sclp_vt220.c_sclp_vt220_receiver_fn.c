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
struct evbuf_header {int length; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
#define  SCLP_VT220_SESSION_DATA 130 
#define  SCLP_VT220_SESSION_ENDED 129 
#define  SCLP_VT220_SESSION_STARTED 128 
 int /*<<< orphan*/ * sclp_vt220_tty ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_string (int /*<<< orphan*/ *,char*,unsigned int) ; 

__attribute__((used)) static void
sclp_vt220_receiver_fn(struct evbuf_header *evbuf)
{
	char *buffer;
	unsigned int count;

	/* Ignore input if device is not open */
	if (sclp_vt220_tty == NULL)
		return;

	buffer = (char *) ((addr_t) evbuf + sizeof(struct evbuf_header));
	count = evbuf->length - sizeof(struct evbuf_header);

	switch (*buffer) {
	case SCLP_VT220_SESSION_ENDED:
	case SCLP_VT220_SESSION_STARTED:
		break;
	case SCLP_VT220_SESSION_DATA:
		/* Send input to line discipline */
		buffer++;
		count--;
		tty_insert_flip_string(sclp_vt220_tty, buffer, count);
		tty_flip_buffer_push(sclp_vt220_tty);
		break;
	}
}