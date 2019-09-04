#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int k; int ksum; } ;
struct TYPE_6__ {int k; int ksum; } ;
struct TYPE_8__ {int fileversion; int data_end; int ptr; int CRC; TYPE_2__ riceY; TYPE_1__ riceX; void* frameflags; int /*<<< orphan*/  gb; } ;
typedef  TYPE_3__ APEContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 void* bytestream_get_be32 (int*) ; 
 int get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  range_start_decoding (TYPE_3__*) ; 

__attribute__((used)) static int init_entropy_decoder(APEContext *ctx)
{
    /* Read the CRC */
    if (ctx->fileversion >= 3900) {
        if (ctx->data_end - ctx->ptr < 6)
            return AVERROR_INVALIDDATA;
        ctx->CRC = bytestream_get_be32(&ctx->ptr);
    } else {
        ctx->CRC = get_bits_long(&ctx->gb, 32);
    }

    /* Read the frame flags if they exist */
    ctx->frameflags = 0;
    if ((ctx->fileversion > 3820) && (ctx->CRC & 0x80000000)) {
        ctx->CRC &= ~0x80000000;

        if (ctx->data_end - ctx->ptr < 6)
            return AVERROR_INVALIDDATA;
        ctx->frameflags = bytestream_get_be32(&ctx->ptr);
    }

    /* Initialize the rice structs */
    ctx->riceX.k = 10;
    ctx->riceX.ksum = (1 << ctx->riceX.k) * 16;
    ctx->riceY.k = 10;
    ctx->riceY.ksum = (1 << ctx->riceY.k) * 16;

    if (ctx->fileversion >= 3900) {
        /* The first 8 bits of input are ignored. */
        ctx->ptr++;

        range_start_decoding(ctx);
    }

    return 0;
}