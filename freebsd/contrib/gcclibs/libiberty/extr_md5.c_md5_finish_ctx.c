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
struct md5_ctx {int buflen; int* total; int /*<<< orphan*/ * buffer; } ;
typedef  int md5_uint32 ;

/* Variables and functions */
 int SWAP (int) ; 
 int /*<<< orphan*/  fillbuf ; 
 int /*<<< orphan*/  md5_process_block (int /*<<< orphan*/ *,int,struct md5_ctx*) ; 
 void* md5_read_ctx (struct md5_ctx*,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

void *
md5_finish_ctx (struct md5_ctx *ctx, void *resbuf)
{
  /* Take yet unprocessed bytes into account.  */
  md5_uint32 bytes = ctx->buflen;
  size_t pad;

  /* Now count remaining bytes.  */
  ctx->total[0] += bytes;
  if (ctx->total[0] < bytes)
    ++ctx->total[1];

  pad = bytes >= 56 ? 64 + 56 - bytes : 56 - bytes;
  memcpy (&ctx->buffer[bytes], fillbuf, pad);

  /* Put the 64-bit file length in *bits* at the end of the buffer.  */
  *(md5_uint32 *) &ctx->buffer[bytes + pad] = SWAP (ctx->total[0] << 3);
  *(md5_uint32 *) &ctx->buffer[bytes + pad + 4] = SWAP ((ctx->total[1] << 3) |
							(ctx->total[0] >> 29));

  /* Process last bytes.  */
  md5_process_block (ctx->buffer, bytes + pad + 8, ctx);

  return md5_read_ctx (ctx, resbuf);
}