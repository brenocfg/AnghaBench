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
struct TYPE_5__ {int chunk_count; TYPE_1__* chunks; } ;
struct TYPE_4__ {size_t compressed_offset; scalar_t__ compressor; scalar_t__ compressed_size; } ;
typedef  TYPE_2__ HapContext ;

/* Variables and functions */
 scalar_t__ HAP_COMP_NONE ; 

__attribute__((used)) static int hap_can_use_tex_in_place(HapContext *ctx)
{
    int i;
    size_t running_offset = 0;
    for (i = 0; i < ctx->chunk_count; i++) {
        if (ctx->chunks[i].compressed_offset != running_offset
            || ctx->chunks[i].compressor != HAP_COMP_NONE)
            return 0;
        running_offset += ctx->chunks[i].compressed_size;
    }
    return 1;
}