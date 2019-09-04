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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ firehose_tracepoint_id_t ;
typedef  scalar_t__ firehose_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,unsigned int,unsigned char const,unsigned char const,...) ; 

firehose_tracepoint_id_t
firehose_debug_trace(firehose_stream_t stream, firehose_tracepoint_id_t trace_id,
		uint64_t timestamp, const char *format, const void *pubdata, size_t publen)
{
	kprintf("[os_log stream 0x%x trace_id 0x%llx timestamp %llu format '%s' data %p len %lu]\n",
			(unsigned int)stream, (unsigned long long)trace_id, timestamp,
			format, pubdata, publen);
	size_t i;
	const unsigned char *cdata = (const unsigned char *)pubdata;
	for (i=0; i < publen; i += 8) {
		kprintf(">oslog 0x%08x: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
				(unsigned int)i,
				(i+0) < publen ? cdata[i+0] : 0,
				(i+1) < publen ? cdata[i+1] : 0,
				(i+2) < publen ? cdata[i+2] : 0,
				(i+3) < publen ? cdata[i+3] : 0,
				(i+4) < publen ? cdata[i+4] : 0,
				(i+5) < publen ? cdata[i+5] : 0,
				(i+6) < publen ? cdata[i+6] : 0,
				(i+7) < publen ? cdata[i+7] : 0
			);
	}
	return trace_id;
}