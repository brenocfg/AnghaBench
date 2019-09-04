#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int max_payload_size; int* buf; int /*<<< orphan*/  cur_timestamp; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ RTPMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int* avpriv_find_start_code (int const*,int const*,int*) ; 
 int /*<<< orphan*/  ff_rtp_send_data (TYPE_2__*,int*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

void ff_rtp_send_mpegvideo(AVFormatContext *s1, const uint8_t *buf1, int size)
{
    RTPMuxContext *s = s1->priv_data;
    int len, h, max_packet_size;
    uint8_t *q;
    const uint8_t *end = buf1 + size;
    int begin_of_slice, end_of_slice, frame_type, temporal_reference;

    max_packet_size = s->max_payload_size;
    begin_of_slice = 1;
    end_of_slice = 0;
    frame_type = 0;
    temporal_reference = 0;

    while (size > 0) {
        int begin_of_sequence;

        begin_of_sequence = 0;
        len = max_packet_size - 4;

        if (len >= size) {
            len = size;
            end_of_slice = 1;
        } else {
            const uint8_t *r, *r1;
            int start_code;

            r1 = buf1;
            while (1) {
                start_code = -1;
                r = avpriv_find_start_code(r1, end, &start_code);
                if((start_code & 0xFFFFFF00) == 0x100) {
                    /* New start code found */
                    if (start_code == 0x100) {
                        frame_type = (r[1] & 0x38) >> 3;
                        temporal_reference = (int)r[0] << 2 | r[1] >> 6;
                    }
                    if (start_code == 0x1B8) {
                        begin_of_sequence = 1;
                    }

                    if (r - buf1 - 4 <= len) {
                        /* The current slice fits in the packet */
                        if (begin_of_slice == 0) {
                            /* no slice at the beginning of the packet... */
                            end_of_slice = 1;
                            len = r - buf1 - 4;
                            break;
                        }
                        r1 = r;
                    } else {
                        if ((r1 - buf1 > 4) && (r - r1 < max_packet_size)) {
                            len = r1 - buf1 - 4;
                            end_of_slice = 1;
                        }
                        break;
                    }
                } else {
                    break;
                }
            }
        }

        h = 0;
        h |= temporal_reference << 16;
        h |= begin_of_sequence << 13;
        h |= begin_of_slice << 12;
        h |= end_of_slice << 11;
        h |= frame_type << 8;

        q = s->buf;
        *q++ = h >> 24;
        *q++ = h >> 16;
        *q++ = h >> 8;
        *q++ = h;

        memcpy(q, buf1, len);
        q += len;

        /* 90kHz time stamp */
        s->timestamp = s->cur_timestamp;
        ff_rtp_send_data(s1, s->buf, q - s->buf, (len == size));

        buf1 += len;
        size -= len;
        begin_of_slice = end_of_slice;
        end_of_slice = 0;
    }
}