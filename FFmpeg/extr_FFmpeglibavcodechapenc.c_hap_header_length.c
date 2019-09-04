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
struct TYPE_4__ {int chunk_count; } ;
typedef  TYPE_1__ HapContext ;

/* Variables and functions */
 int HAP_HDR_LONG ; 
 scalar_t__ HAP_HDR_SHORT ; 
 scalar_t__ hap_decode_instructions_length (TYPE_1__*) ; 

__attribute__((used)) static int hap_header_length(HapContext *ctx)
{
    /* Top section header (long version) */
    int length = HAP_HDR_LONG;

    if (ctx->chunk_count > 1) {
        /* Decode Instructions header (short) + Decode Instructions Container */
        length += HAP_HDR_SHORT + hap_decode_instructions_length(ctx);
    }

    return length;
}