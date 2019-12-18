#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int /*<<< orphan*/  decode_buffer_2; int /*<<< orphan*/  decode_buffer_1; } ;
struct TYPE_12__ {int size; int num_channels; size_t ch_idx; int /*<<< orphan*/  mono_previous_buffer2; int /*<<< orphan*/  gains2; int /*<<< orphan*/  gains1; scalar_t__ joint_stereo; int /*<<< orphan*/  mono_previous_buffer1; } ;
typedef  TYPE_1__ COOKSubpacket ;
typedef  TYPE_2__ COOKContext ;

/* Variables and functions */
 int /*<<< orphan*/  decode_bytes_and_gain (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int joint_decode (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlt_compensate_output (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*) ; 
 int mono_decode (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_subpacket(COOKContext *q, COOKSubpacket *p,
                            const uint8_t *inbuffer, float **outbuffer)
{
    int sub_packet_size = p->size;
    int res;

    memset(q->decode_buffer_1, 0, sizeof(q->decode_buffer_1));
    decode_bytes_and_gain(q, p, inbuffer, &p->gains1);

    if (p->joint_stereo) {
        if ((res = joint_decode(q, p, q->decode_buffer_1, q->decode_buffer_2)) < 0)
            return res;
    } else {
        if ((res = mono_decode(q, p, q->decode_buffer_1)) < 0)
            return res;

        if (p->num_channels == 2) {
            decode_bytes_and_gain(q, p, inbuffer + sub_packet_size / 2, &p->gains2);
            if ((res = mono_decode(q, p, q->decode_buffer_2)) < 0)
                return res;
        }
    }

    mlt_compensate_output(q, q->decode_buffer_1, &p->gains1,
                          p->mono_previous_buffer1,
                          outbuffer ? outbuffer[p->ch_idx] : NULL);

    if (p->num_channels == 2) {
        if (p->joint_stereo)
            mlt_compensate_output(q, q->decode_buffer_2, &p->gains1,
                                  p->mono_previous_buffer2,
                                  outbuffer ? outbuffer[p->ch_idx + 1] : NULL);
        else
            mlt_compensate_output(q, q->decode_buffer_2, &p->gains2,
                                  p->mono_previous_buffer2,
                                  outbuffer ? outbuffer[p->ch_idx + 1] : NULL);
    }

    return 0;
}