#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int len; int /*<<< orphan*/ * ABCD; } ;
typedef  TYPE_1__ AVMD5 ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WL32 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_le2ne64 (int) ; 
 int /*<<< orphan*/  av_md5_update (TYPE_1__*,char*,int) ; 

void av_md5_final(AVMD5 *ctx, uint8_t *dst)
{
    int i;
    uint64_t finalcount = av_le2ne64(ctx->len << 3);

    av_md5_update(ctx, "\200", 1);
    while ((ctx->len & 63) != 56)
        av_md5_update(ctx, "", 1);

    av_md5_update(ctx, (uint8_t *) &finalcount, 8);

    for (i = 0; i < 4; i++)
        AV_WL32(dst + 4 * i, ctx->ABCD[3 - i]);
}