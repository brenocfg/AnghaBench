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
struct TYPE_3__ {int /*<<< orphan*/  frm1_size; int /*<<< orphan*/  frm1; int /*<<< orphan*/  frm0; } ;
typedef  TYPE_1__ SANMVideoContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_4(SANMVideoContext *ctx)
{
    memcpy(ctx->frm0, ctx->frm1, ctx->frm1_size);
    return 0;
}