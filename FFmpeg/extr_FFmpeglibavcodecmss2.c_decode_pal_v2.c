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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int pal; int free_colours; } ;
typedef  TYPE_1__ MSS12Context ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_RB24 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int decode_pal_v2(MSS12Context *ctx, const uint8_t *buf, int buf_size)
{
    int i, ncol;
    uint32_t *pal = ctx->pal + 256 - ctx->free_colours;

    if (!ctx->free_colours)
        return 0;

    ncol = *buf++;
    if (ncol > ctx->free_colours || buf_size < 2 + ncol * 3)
        return AVERROR_INVALIDDATA;
    for (i = 0; i < ncol; i++)
        *pal++ = AV_RB24(buf + 3 * i);

    return 1 + ncol * 3;
}