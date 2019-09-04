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
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ ThresholdContext ;
struct TYPE_5__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int ff_framesync_activate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    ThresholdContext *s = ctx->priv;
    return ff_framesync_activate(&s->fs);
}