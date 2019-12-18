#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  TYPE_1__* ringbuf_t ;
struct TYPE_5__ {int /*<<< orphan*/  const* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  lwIP_ASSERT (int) ; 
 int ringbuf_buffer_size (TYPE_1__*) ; 
 int /*<<< orphan*/  const* ringbuf_end (TYPE_1__*) ; 

__attribute__((used)) static uint8_t *ringbuf_nextp(ringbuf_t rb, const uint8_t *p)
{
	lwIP_ASSERT((p >= rb->buf) && (p < ringbuf_end(rb)));
	return rb->buf + ((++p -rb->buf) % ringbuf_buffer_size(rb));
}