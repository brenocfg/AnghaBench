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
struct TYPE_4__ {int count; int digest_len; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ AVSHA ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB32 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_be2ne64 (int) ; 
 int /*<<< orphan*/  av_sha_update (TYPE_1__*,char*,int) ; 

void av_sha_final(AVSHA* ctx, uint8_t *digest)
{
    int i;
    uint64_t finalcount = av_be2ne64(ctx->count << 3);

    av_sha_update(ctx, "\200", 1);
    while ((ctx->count & 63) != 56)
        av_sha_update(ctx, "", 1);
    av_sha_update(ctx, (uint8_t *)&finalcount, 8); /* Should cause a transform() */
    for (i = 0; i < ctx->digest_len; i++)
        AV_WB32(digest + i*4, ctx->state[i]);
}