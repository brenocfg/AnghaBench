#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_1__* src; } ;
struct TYPE_6__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ PadContext ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    PadContext *s = outlink->src->priv;

    outlink->w = s->w;
    outlink->h = s->h;
    return 0;
}