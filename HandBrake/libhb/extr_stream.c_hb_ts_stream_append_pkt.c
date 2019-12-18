#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {TYPE_1__* list; } ;
struct TYPE_8__ {TYPE_2__ ts; } ;
typedef  TYPE_3__ hb_stream_t ;
struct TYPE_9__ {int size; int alloc; scalar_t__ data; } ;
struct TYPE_6__ {int packet_len; TYPE_5__* buf; scalar_t__ skipbad; } ;

/* Variables and functions */
 int MAX (int,int) ; 
 int /*<<< orphan*/  hb_buffer_realloc (TYPE_5__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void hb_ts_stream_append_pkt(hb_stream_t *stream, int idx,
                                    const uint8_t *buf, int len)
{
    if (stream->ts.list[idx].skipbad || len <= 0)
        return;

    if (stream->ts.list[idx].buf->size + len > stream->ts.list[idx].buf->alloc)
    {
        int size;

        size = MAX(stream->ts.list[idx].buf->alloc * 2,
                   stream->ts.list[idx].buf->size + len);
        hb_buffer_realloc(stream->ts.list[idx].buf, size);
    }
    memcpy(stream->ts.list[idx].buf->data + stream->ts.list[idx].buf->size,
           buf, len);
    stream->ts.list[idx].buf->size += len;
    stream->ts.list[idx].packet_len += len;
}