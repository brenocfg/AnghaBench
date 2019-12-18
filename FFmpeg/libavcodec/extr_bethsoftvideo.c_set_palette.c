#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_1__* frame; int /*<<< orphan*/  g; } ;
struct TYPE_4__ {int palette_has_changed; scalar_t__* data; } ;
typedef  TYPE_2__ BethsoftvidContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int bytestream2_get_be24u (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_palette(BethsoftvidContext *ctx)
{
    uint32_t *palette = (uint32_t *)ctx->frame->data[1];
    int a;

    if (bytestream2_get_bytes_left(&ctx->g) < 256*3)
        return AVERROR_INVALIDDATA;

    for(a = 0; a < 256; a++){
        palette[a] = 0xFFU << 24 | bytestream2_get_be24u(&ctx->g) * 4;
        palette[a] |= palette[a] >> 6 & 0x30303;
    }
    ctx->frame->palette_has_changed = 1;
    return 0;
}