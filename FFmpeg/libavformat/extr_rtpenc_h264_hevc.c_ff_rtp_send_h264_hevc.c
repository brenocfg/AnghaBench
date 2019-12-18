#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {scalar_t__ nal_length_size; int /*<<< orphan*/  buf; int /*<<< orphan*/  buf_ptr; int /*<<< orphan*/  cur_timestamp; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ RTPMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/ * ff_avc_find_startcode (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ff_avc_mp4_find_startcode (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  flush_buffered (TYPE_2__*,int) ; 
 int /*<<< orphan*/  nal_send (TYPE_2__*,int /*<<< orphan*/  const*,int,int) ; 

void ff_rtp_send_h264_hevc(AVFormatContext *s1, const uint8_t *buf1, int size)
{
    const uint8_t *r, *end = buf1 + size;
    RTPMuxContext *s = s1->priv_data;

    s->timestamp = s->cur_timestamp;
    s->buf_ptr   = s->buf;
    if (s->nal_length_size)
        r = ff_avc_mp4_find_startcode(buf1, end, s->nal_length_size) ? buf1 : end;
    else
        r = ff_avc_find_startcode(buf1, end);
    while (r < end) {
        const uint8_t *r1;

        if (s->nal_length_size) {
            r1 = ff_avc_mp4_find_startcode(r, end, s->nal_length_size);
            if (!r1)
                r1 = end;
            r += s->nal_length_size;
        } else {
            while (!*(r++));
            r1 = ff_avc_find_startcode(r, end);
        }
        nal_send(s1, r, r1 - r, r1 == end);
        r = r1;
    }
    flush_buffered(s1, 1);
}