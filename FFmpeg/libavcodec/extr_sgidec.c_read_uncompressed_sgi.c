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
typedef  unsigned char uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {unsigned int height; unsigned int width; unsigned int bytes_per_channel; unsigned int depth; int linesize; int /*<<< orphan*/  g; } ;
typedef  TYPE_1__ SgiState ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 unsigned int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_ne16u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_uncompressed_sgi(unsigned char *out_buf, SgiState *s)
{
    int x, y, z;
    unsigned int offset = s->height * s->width * s->bytes_per_channel;
    GetByteContext gp[4];
    uint8_t *out_end;

    /* Test buffer size. */
    if (offset * s->depth > bytestream2_get_bytes_left(&s->g))
        return AVERROR_INVALIDDATA;

    /* Create a reader for each plane */
    for (z = 0; z < s->depth; z++) {
        gp[z] = s->g;
        bytestream2_skip(&gp[z], z * offset);
    }

    for (y = s->height - 1; y >= 0; y--) {
        out_end = out_buf + (y * s->linesize);
        if (s->bytes_per_channel == 1) {
            for (x = s->width; x > 0; x--)
                for (z = 0; z < s->depth; z++)
                    *out_end++ = bytestream2_get_byteu(&gp[z]);
        } else {
            uint16_t *out16 = (uint16_t *)out_end;
            for (x = s->width; x > 0; x--)
                for (z = 0; z < s->depth; z++)
                    *out16++ = bytestream2_get_ne16u(&gp[z]);
        }
    }
    return 0;
}