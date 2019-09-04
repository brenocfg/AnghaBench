#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int stride; int /*<<< orphan*/  stream_ptr; int /*<<< orphan*/  line_inc; scalar_t__ pixel_ptr; } ;
typedef  TYPE_1__ IpvideoContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipvideo_decode_block_opcode_0x9_16(IpvideoContext *s, AVFrame *frame)
{
    int x, y;
    uint16_t P[4];
    uint16_t *pixel_ptr = (uint16_t*)s->pixel_ptr;

    /* 4-color encoding */
    for (x = 0; x < 4; x++)
        P[x] = bytestream2_get_le16(&s->stream_ptr);

    if (!(P[0] & 0x8000)) {
        if (!(P[2] & 0x8000)) {

            /* 1 of 4 colors for each pixel */
            for (y = 0; y < 8; y++) {
                /* get the next set of 8 2-bit flags */
                int flags = bytestream2_get_le16(&s->stream_ptr);
                for (x = 0; x < 8; x++, flags >>= 2)
                    *pixel_ptr++ = P[flags & 0x03];
                pixel_ptr += s->line_inc;
            }

        } else {
            uint32_t flags;

            /* 1 of 4 colors for each 2x2 block */
            flags = bytestream2_get_le32(&s->stream_ptr);

            for (y = 0; y < 8; y += 2) {
                for (x = 0; x < 8; x += 2, flags >>= 2) {
                    pixel_ptr[x                ] =
                    pixel_ptr[x + 1            ] =
                    pixel_ptr[x +     s->stride] =
                    pixel_ptr[x + 1 + s->stride] = P[flags & 0x03];
                }
                pixel_ptr += s->stride * 2;
            }

        }
    } else {
        uint64_t flags;

        /* 1 of 4 colors for each 2x1 or 1x2 block */
        flags = bytestream2_get_le64(&s->stream_ptr);
        if (!(P[2] & 0x8000)) {
            for (y = 0; y < 8; y++) {
                for (x = 0; x < 8; x += 2, flags >>= 2) {
                    pixel_ptr[x    ] =
                    pixel_ptr[x + 1] = P[flags & 0x03];
                }
                pixel_ptr += s->stride;
            }
        } else {
            for (y = 0; y < 8; y += 2) {
                for (x = 0; x < 8; x++, flags >>= 2) {
                    pixel_ptr[x            ] =
                    pixel_ptr[x + s->stride] = P[flags & 0x03];
                }
                pixel_ptr += s->stride * 2;
            }
        }
    }

    /* report success */
    return 0;
}