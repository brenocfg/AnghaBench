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
typedef  int uint32_t ;
struct TYPE_3__ {int* palette; int /*<<< orphan*/  gb; int /*<<< orphan*/  hdr_state; } ;
typedef  TYPE_1__ PNGDecContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  PNG_PLTE ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_plte_chunk(AVCodecContext *avctx, PNGDecContext *s,
                             uint32_t length)
{
    int n, i, r, g, b;

    if ((length % 3) != 0 || length > 256 * 3)
        return AVERROR_INVALIDDATA;
    /* read the palette */
    n = length / 3;
    for (i = 0; i < n; i++) {
        r = bytestream2_get_byte(&s->gb);
        g = bytestream2_get_byte(&s->gb);
        b = bytestream2_get_byte(&s->gb);
        s->palette[i] = (0xFFU << 24) | (r << 16) | (g << 8) | b;
    }
    for (; i < 256; i++)
        s->palette[i] = (0xFFU << 24);
    s->hdr_state |= PNG_PLTE;
    bytestream2_skip(&s->gb, 4);     /* crc */

    return 0;
}