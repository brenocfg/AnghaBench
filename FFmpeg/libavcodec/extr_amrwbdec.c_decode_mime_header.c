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
typedef  int uint8_t ;
struct TYPE_3__ {int fr_cur_mode; int fr_quality; } ;
typedef  TYPE_1__ AMRWBContext ;

/* Variables and functions */

__attribute__((used)) static int decode_mime_header(AMRWBContext *ctx, const uint8_t *buf)
{
    /* Decode frame header (1st octet) */
    ctx->fr_cur_mode  = buf[0] >> 3 & 0x0F;
    ctx->fr_quality   = (buf[0] & 0x4) == 0x4;

    return 1;
}