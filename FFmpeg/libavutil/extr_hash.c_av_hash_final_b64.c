#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct AVHashContext {int dummy; } ;
typedef  int /*<<< orphan*/  b64 ;

/* Variables and functions */
 int AV_BASE64_SIZE (unsigned int) ; 
 int AV_HASH_MAX_SIZE ; 
 int /*<<< orphan*/  FFMIN (unsigned int,int) ; 
 int /*<<< orphan*/  av_base64_encode (scalar_t__*,int,scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/  av_hash_final (struct AVHashContext*,scalar_t__*) ; 
 unsigned int av_hash_get_size (struct AVHashContext*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

void av_hash_final_b64(struct AVHashContext *ctx, uint8_t *dst, int size)
{
    uint8_t buf[AV_HASH_MAX_SIZE], b64[AV_BASE64_SIZE(AV_HASH_MAX_SIZE)];
    unsigned rsize = av_hash_get_size(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, sizeof(b64), buf, rsize);
    osize = AV_BASE64_SIZE(rsize);
    memcpy(dst, b64, FFMIN(osize, size));
    if (size < osize)
        dst[size - 1] = 0;
}