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
struct TYPE_4__ {int /*<<< orphan*/  riceY; int /*<<< orphan*/ * decoded; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ APEContext ;

/* Variables and functions */
 int /*<<< orphan*/  decode_array_0000 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void entropy_decode_mono_0000(APEContext *ctx, int blockstodecode)
{
    decode_array_0000(ctx, &ctx->gb, ctx->decoded[0], &ctx->riceY,
                      blockstodecode);
}