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
struct md5_ctx {scalar_t__ buflen; scalar_t__* total; void* D; void* C; void* B; void* A; } ;
typedef  void* md5_uint32 ;

/* Variables and functions */

void
md5_init_ctx (struct md5_ctx *ctx)
{
  ctx->A = (md5_uint32) 0x67452301;
  ctx->B = (md5_uint32) 0xefcdab89;
  ctx->C = (md5_uint32) 0x98badcfe;
  ctx->D = (md5_uint32) 0x10325476;

  ctx->total[0] = ctx->total[1] = 0;
  ctx->buflen = 0;
}