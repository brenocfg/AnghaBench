#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int help; int range; int low; } ;
struct TYPE_6__ {TYPE_1__ rc; } ;
typedef  TYPE_2__ APEContext ;

/* Variables and functions */
 int /*<<< orphan*/  range_dec_normalize (TYPE_2__*) ; 

__attribute__((used)) static inline int range_decode_culfreq(APEContext *ctx, int tot_f)
{
    range_dec_normalize(ctx);
    ctx->rc.help = ctx->rc.range / tot_f;
    return ctx->rc.low / ctx->rc.help;
}