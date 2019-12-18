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
struct xdr_buf {unsigned int page_len; scalar_t__ buflen; scalar_t__ len; scalar_t__ page_base; int /*<<< orphan*/  pages; struct kvec* head; struct kvec* tail; } ;
struct kvec {size_t iov_len; scalar_t__ iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  _copy_from_pages (char*,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  _copy_to_pages (int /*<<< orphan*/ ,scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  _shift_data_right_pages (int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,scalar_t__,size_t) ; 

__attribute__((used)) static void
xdr_shrink_bufhead(struct xdr_buf *buf, size_t len)
{
	struct kvec *head, *tail;
	size_t copy, offs;
	unsigned int pglen = buf->page_len;

	tail = buf->tail;
	head = buf->head;
	BUG_ON (len > head->iov_len);

	/* Shift the tail first */
	if (tail->iov_len != 0) {
		if (tail->iov_len > len) {
			copy = tail->iov_len - len;
			memmove((char *)tail->iov_base + len,
					tail->iov_base, copy);
		}
		/* Copy from the inlined pages into the tail */
		copy = len;
		if (copy > pglen)
			copy = pglen;
		offs = len - copy;
		if (offs >= tail->iov_len)
			copy = 0;
		else if (copy > tail->iov_len - offs)
			copy = tail->iov_len - offs;
		if (copy != 0)
			_copy_from_pages((char *)tail->iov_base + offs,
					buf->pages,
					buf->page_base + pglen + offs - len,
					copy);
		/* Do we also need to copy data from the head into the tail ? */
		if (len > pglen) {
			offs = copy = len - pglen;
			if (copy > tail->iov_len)
				copy = tail->iov_len;
			memcpy(tail->iov_base,
					(char *)head->iov_base +
					head->iov_len - offs,
					copy);
		}
	}
	/* Now handle pages */
	if (pglen != 0) {
		if (pglen > len)
			_shift_data_right_pages(buf->pages,
					buf->page_base + len,
					buf->page_base,
					pglen - len);
		copy = len;
		if (len > pglen)
			copy = pglen;
		_copy_to_pages(buf->pages, buf->page_base,
				(char *)head->iov_base + head->iov_len - len,
				copy);
	}
	head->iov_len -= len;
	buf->buflen -= len;
	/* Have we truncated the message? */
	if (buf->len > buf->buflen)
		buf->len = buf->buflen;
}