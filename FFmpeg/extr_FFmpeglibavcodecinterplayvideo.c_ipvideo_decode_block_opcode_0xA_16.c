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
typedef  int uint16_t ;
struct TYPE_3__ {int stride; int /*<<< orphan*/  stream_ptr; int /*<<< orphan*/  line_inc; scalar_t__ pixel_ptr; } ;
typedef  TYPE_1__ IpvideoContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int ipvideo_decode_block_opcode_0xA_16(IpvideoContext *s, AVFrame *frame)
{
    int x, y;
    uint16_t P[8];
    int flags = 0;
    uint16_t *pixel_ptr = (uint16_t*)s->pixel_ptr;

    for (x = 0; x < 4; x++)
        P[x] = bytestream2_get_le16(&s->stream_ptr);

    /* 4-color encoding for each 4x4 quadrant, or 4-color encoding on
     * either top and bottom or left and right halves */
    if (!(P[0] & 0x8000)) {

        /* 4-color encoding for each quadrant */
        for (y = 0; y < 16; y++) {
            // new values for each 4x4 block
            if (!(y & 3)) {
                if (y)
                    for (x = 0; x < 4; x++)
                        P[x] = bytestream2_get_le16(&s->stream_ptr);
                flags = bytestream2_get_le32(&s->stream_ptr);
            }

            for (x = 0; x < 4; x++, flags >>= 2)
                *pixel_ptr++ = P[flags & 0x03];

            pixel_ptr += s->stride - 4;
            // switch to right half
            if (y == 7) pixel_ptr -= 8 * s->stride - 4;
        }

    } else {
        // vertical split?
        int vert;
        uint64_t flags = bytestream2_get_le64(&s->stream_ptr);

        for (x = 4; x < 8; x++)
            P[x] = bytestream2_get_le16(&s->stream_ptr);
        vert = !(P[4] & 0x8000);

        /* 4-color encoding for either left and right or top and bottom
         * halves */

        for (y = 0; y < 16; y++) {
            for (x = 0; x < 4; x++, flags >>= 2)
                *pixel_ptr++ = P[flags & 0x03];

            if (vert) {
                pixel_ptr += s->stride - 4;
                // switch to right half
                if (y == 7) pixel_ptr -= 8 * s->stride - 4;
            } else if (y & 1) pixel_ptr += s->line_inc;

            // load values for second half
            if (y == 7) {
                memcpy(P, P + 4, 8);
                flags = bytestream2_get_le64(&s->stream_ptr);
            }
        }
    }

    /* report success */
    return 0;
}