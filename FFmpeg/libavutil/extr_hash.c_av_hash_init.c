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
struct TYPE_3__ {int type; int crc; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ AVHashContext ;

/* Variables and functions */
#define  ADLER32 142 
#define  CRC32 141 
#define  MD5 140 
#define  MURMUR3 139 
#define  RIPEMD128 138 
#define  RIPEMD160 137 
#define  RIPEMD256 136 
#define  RIPEMD320 135 
#define  SHA160 134 
#define  SHA224 133 
#define  SHA256 132 
#define  SHA384 131 
#define  SHA512 130 
#define  SHA512_224 129 
#define  SHA512_256 128 
 int UINT32_MAX ; 
 int /*<<< orphan*/  av_md5_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_murmur3_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_ripemd_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_sha512_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_sha_init (int /*<<< orphan*/ ,int) ; 

void av_hash_init(AVHashContext *ctx)
{
    switch (ctx->type) {
    case MD5:     av_md5_init(ctx->ctx); break;
    case MURMUR3: av_murmur3_init(ctx->ctx); break;
    case RIPEMD128: av_ripemd_init(ctx->ctx, 128); break;
    case RIPEMD160: av_ripemd_init(ctx->ctx, 160); break;
    case RIPEMD256: av_ripemd_init(ctx->ctx, 256); break;
    case RIPEMD320: av_ripemd_init(ctx->ctx, 320); break;
    case SHA160:  av_sha_init(ctx->ctx, 160); break;
    case SHA224:  av_sha_init(ctx->ctx, 224); break;
    case SHA256:  av_sha_init(ctx->ctx, 256); break;
    case SHA512_224:  av_sha512_init(ctx->ctx, 224); break;
    case SHA512_256:  av_sha512_init(ctx->ctx, 256); break;
    case SHA384:  av_sha512_init(ctx->ctx, 384); break;
    case SHA512:  av_sha512_init(ctx->ctx, 512); break;
    case CRC32:   ctx->crc = UINT32_MAX; break;
    case ADLER32: ctx->crc = 1; break;
    }
}