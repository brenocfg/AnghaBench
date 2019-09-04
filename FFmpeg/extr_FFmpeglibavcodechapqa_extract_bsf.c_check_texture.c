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
struct TYPE_3__ {int texture; } ;
typedef  TYPE_1__ HapqaExtractContext ;

/* Variables and functions */

__attribute__((used)) static int check_texture(HapqaExtractContext *ctx, int section_type) {
    if (((ctx->texture == 0)&&((section_type & 0x0F) == 0x0F)) || /* HapQ texture and rgb extract */
        ((ctx->texture == 1)&&((section_type & 0x0F) == 0x01))) /* HapAlphaOnly texture and alpha extract */
    {
        return 1; /* the texture is the one to keep */
    } else {
        return 0;
    }
}