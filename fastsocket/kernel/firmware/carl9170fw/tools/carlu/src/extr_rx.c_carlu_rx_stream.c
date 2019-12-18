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
struct frame {unsigned int len; void* data; } ;
struct carlu {int dummy; } ;
struct ar9170_stream {scalar_t__ tag; void* payload; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  __carlu_rx (struct carlu*,void*,unsigned int) ; 
 scalar_t__ cpu_to_le16 (int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (int /*<<< orphan*/ ,char*,void*,unsigned int) ; 
 unsigned int roundup (unsigned int,int) ; 
 int /*<<< orphan*/  warn (char*,void*,int,scalar_t__) ; 

__attribute__((used)) static void carlu_rx_stream(struct carlu *ar, struct frame *frame)
{
	void *buf = frame->data;
	unsigned int len = frame->len;

	while (len >= 4) {
		struct ar9170_stream *rx_stream;
		unsigned int resplen, elen;

		rx_stream = (void *) buf;
		resplen = le16_to_cpu(rx_stream->length);
		elen = roundup(resplen + 4, 4);

		if (rx_stream->tag != cpu_to_le16(0x4e00)) {
			warn("frame has no tag %p %u %x.\n",
			      buf, (int) len, rx_stream->tag);
			print_hex_dump_bytes(WARNING, "FRAME:", frame->data, frame->len);

			__carlu_rx(ar, buf, len);
			return;
		}

		__carlu_rx(ar, rx_stream->payload, resplen);

		len -= elen;
		buf += elen;
	}
}