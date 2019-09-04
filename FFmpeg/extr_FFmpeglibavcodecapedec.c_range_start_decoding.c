#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int buffer; int low; int range; } ;
struct TYPE_5__ {TYPE_1__ rc; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ APEContext ;

/* Variables and functions */
 int EXTRA_BITS ; 
 int bytestream_get_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void range_start_decoding(APEContext *ctx)
{
    ctx->rc.buffer = bytestream_get_byte(&ctx->ptr);
    ctx->rc.low    = ctx->rc.buffer >> (8 - EXTRA_BITS);
    ctx->rc.range  = (uint32_t) 1 << EXTRA_BITS;
}