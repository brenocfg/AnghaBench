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
struct TYPE_4__ {unsigned long lo; void const* buffer; scalar_t__ hi; } ;
typedef  unsigned long MD5_u32plus ;
typedef  TYPE_1__ MD5_CTX ;

/* Variables and functions */
 void* body (TYPE_1__*,void const*,unsigned long) ; 
 int /*<<< orphan*/  memcpy (void const*,void const*,unsigned long) ; 

__attribute__((used)) static void MD5_Update(MD5_CTX *ctx, const void *data, unsigned long size)
{
  MD5_u32plus saved_lo;
  unsigned long used;

  saved_lo = ctx->lo;
  ctx->lo = (saved_lo + size) & 0x1fffffff;
  if(ctx->lo < saved_lo)
    ctx->hi++;
  ctx->hi += (MD5_u32plus)size >> 29;

  used = saved_lo & 0x3f;

  if(used) {
    unsigned long available = 64 - used;

    if(size < available) {
      memcpy(&ctx->buffer[used], data, size);
      return;
    }

    memcpy(&ctx->buffer[used], data, available);
    data = (const unsigned char *)data + available;
    size -= available;
    body(ctx, ctx->buffer, 64);
  }

  if(size >= 64) {
    data = body(ctx, data, size & ~(unsigned long)0x3f);
    size &= 0x3f;
  }

  memcpy(ctx->buffer, data, size);
}