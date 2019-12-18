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
struct TYPE_4__ {int low; int help; int range; } ;
struct TYPE_5__ {TYPE_1__ rc; } ;
typedef  TYPE_2__ APEContext ;

/* Variables and functions */

__attribute__((used)) static inline void range_decode_update(APEContext *ctx, int sy_f, int lt_f)
{
    ctx->rc.low  -= ctx->rc.help * lt_f;
    ctx->rc.range = ctx->rc.help * sy_f;
}