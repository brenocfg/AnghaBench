#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void uint8_t ;
typedef  TYPE_1__* ringbuf_t ;
struct TYPE_7__ {void const* head; void const* buf; int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 size_t LWIP_MIN (int,size_t) ; 
 int /*<<< orphan*/  lwIP_ASSERT (int) ; 
 int /*<<< orphan*/  os_memcpy (void const*,void const*,size_t) ; 
 size_t ringbuf_bytes_free (TYPE_1__*) ; 
 void* ringbuf_end (TYPE_1__*) ; 
 int ringbuf_is_full (TYPE_1__*) ; 
 int /*<<< orphan*/  ringbuf_nextp (TYPE_1__*,void const*) ; 

void *ringbuf_memcpy_into(ringbuf_t dst,const void *src, size_t count)
{
	const uint8_t *u8src = src;
	const uint8_t *bufend = ringbuf_end(dst);
	int overflow = count > ringbuf_bytes_free(dst);
	size_t nread = 0;

	while (nread != count){
		lwIP_ASSERT(bufend > dst->head);
		size_t n = LWIP_MIN(bufend - dst->head, count - nread);
		os_memcpy(dst->head, u8src + nread, n);
		dst->head += n;
		nread += n;

		if (dst->head == bufend)
			dst->head = dst->buf;
	}

	if (overflow) {
		dst->tail = ringbuf_nextp(dst, dst->head);
		lwIP_ASSERT(ringbuf_is_full(dst));
	}

	return dst->head;
}