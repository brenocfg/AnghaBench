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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  riceY; int /*<<< orphan*/ ** decoded; } ;
typedef  TYPE_1__ APEContext ;

/* Variables and functions */
 int /*<<< orphan*/  ape_decode_value_3900 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void entropy_decode_mono_3900(APEContext *ctx, int blockstodecode)
{
    int32_t *decoded0 = ctx->decoded[0];

    while (blockstodecode--)
        *decoded0++ = ape_decode_value_3900(ctx, &ctx->riceY);
}