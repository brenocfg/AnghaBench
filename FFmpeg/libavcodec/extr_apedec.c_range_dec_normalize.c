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
struct TYPE_4__ {int range; int buffer; int low; } ;
struct TYPE_5__ {int error; TYPE_1__ rc; scalar_t__* ptr; scalar_t__* data_end; } ;
typedef  TYPE_2__ APEContext ;

/* Variables and functions */
 int BOTTOM_VALUE ; 

__attribute__((used)) static inline void range_dec_normalize(APEContext *ctx)
{
    while (ctx->rc.range <= BOTTOM_VALUE) {
        ctx->rc.buffer <<= 8;
        if(ctx->ptr < ctx->data_end) {
            ctx->rc.buffer += *ctx->ptr;
            ctx->ptr++;
        } else {
            ctx->error = 1;
        }
        ctx->rc.low    = (ctx->rc.low << 8)    | ((ctx->rc.buffer >> 1) & 0xFF);
        ctx->rc.range  <<= 8;
    }
}