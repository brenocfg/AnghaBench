#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_1__* ringbuf_t ;
struct TYPE_8__ {int /*<<< orphan*/  const* head; int /*<<< orphan*/  tail; int /*<<< orphan*/  const* buf; } ;

/* Variables and functions */
 size_t LWIP_MIN (int,size_t) ; 
 int /*<<< orphan*/  lwIP_ASSERT (int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/  const*,int,size_t) ; 
 size_t ringbuf_buffer_size (TYPE_1__*) ; 
 size_t ringbuf_bytes_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * ringbuf_end (TYPE_1__*) ; 
 int ringbuf_is_full (TYPE_1__*) ; 
 int /*<<< orphan*/  ringbuf_nextp (TYPE_1__*,int /*<<< orphan*/  const*) ; 

size_t ringbuf_memset(ringbuf_t dst, int c, size_t len)
{
	const uint8_t *bufend = ringbuf_end(dst);
	size_t nwritten = 0;
	size_t count = LWIP_MIN(len, ringbuf_buffer_size(dst));
	int overflow = count > ringbuf_bytes_free(dst);

	while (nwritten != count){

		lwIP_ASSERT(bufend > dst->head);
		size_t n = LWIP_MIN(bufend - dst->head, count - nwritten);
		os_memset(dst->head, c, n);
		dst->head += n;
		nwritten += n;

		if (dst->head == bufend)
			dst->head = dst->buf;
	}

	if (overflow){
		dst->tail = ringbuf_nextp(dst, dst->head);
		lwIP_ASSERT(ringbuf_is_full(dst));
	}

	return nwritten;
}