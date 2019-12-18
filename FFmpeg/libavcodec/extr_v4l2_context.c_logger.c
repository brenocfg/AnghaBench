#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  V4L2Context ;
struct TYPE_2__ {int /*<<< orphan*/ * priv; } ;
typedef  int /*<<< orphan*/  AVClass ;

/* Variables and functions */
 TYPE_1__* ctx_to_m2mctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline AVClass *logger(V4L2Context *ctx)
{
    return ctx_to_m2mctx(ctx)->priv;
}