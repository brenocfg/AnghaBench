#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  err; int /*<<< orphan*/  iomode; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */
 int /*<<< orphan*/  BR_ERR_BAD_PARAM ; 
 int /*<<< orphan*/  BR_IO_FAILED ; 
 int MAX_IN_OVERHEAD ; 
 int MAX_OUT_OVERHEAD ; 
 int /*<<< orphan*/  br_ssl_engine_set_buffers_bidi (TYPE_1__*,void*,size_t,unsigned char*,size_t) ; 

void
br_ssl_engine_set_buffer(br_ssl_engine_context *rc,
	void *buf, size_t buf_len, int bidi)
{
	if (buf == NULL) {
		br_ssl_engine_set_buffers_bidi(rc, NULL, 0, NULL, 0);
	} else {
		/*
		 * In bidirectional mode, we want to maximise input
		 * buffer size, since we support arbitrary fragmentation
		 * when sending, but the peer will not necessarily
		 * comply to any low fragment length (in particular if
		 * we are the server, because the maximum fragment
		 * length extension is under client control).
		 *
		 * We keep a minimum size of 512 bytes for the plaintext
		 * of our outgoing records.
		 *
		 * br_ssl_engine_set_buffers_bidi() will compute the maximum
		 * fragment length for outgoing records by using the minimum
		 * of allocated spaces for both input and output records,
		 * rounded down to a standard length.
		 */
		if (bidi) {
			size_t w;

			if (buf_len < (512 + MAX_IN_OVERHEAD
				+ 512 + MAX_OUT_OVERHEAD))
			{
				rc->iomode = BR_IO_FAILED;
				rc->err = BR_ERR_BAD_PARAM;
				return;
			} else if (buf_len < (16384 + MAX_IN_OVERHEAD
				+ 512 + MAX_OUT_OVERHEAD))
			{
				w = 512 + MAX_OUT_OVERHEAD;
			} else {
				w = buf_len - (16384 + MAX_IN_OVERHEAD);
			}
			br_ssl_engine_set_buffers_bidi(rc,
				buf, buf_len - w,
				(unsigned char *)buf + w, w);
		} else {
			br_ssl_engine_set_buffers_bidi(rc,
				buf, buf_len, NULL, 0);
		}
	}
}