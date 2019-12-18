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
struct wpabuf {scalar_t__ used; scalar_t__ size; } ;

/* Variables and functions */
 int wpabuf_len (struct wpabuf*) ; 
 void* wpabuf_mhead_u8 (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_overflow (struct wpabuf*,size_t) ; 

void * wpabuf_put(struct wpabuf *buf, size_t len)
{
	void *tmp = wpabuf_mhead_u8(buf) + wpabuf_len(buf);
	buf->used += len;
	if (buf->used > buf->size) {
		wpabuf_overflow(buf, len);
	}
	return tmp;
}