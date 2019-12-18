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
struct TYPE_2__ {scalar_t__ tv64; } ;
struct timerfd_ctx {TYPE_1__ moffs; int /*<<< orphan*/  might_cancel; } ;

/* Variables and functions */
 scalar_t__ KTIME_MAX ; 
 TYPE_1__ ktime_get_monotonic_offset () ; 

__attribute__((used)) static bool timerfd_canceled(struct timerfd_ctx *ctx)
{
	if (!ctx->might_cancel || ctx->moffs.tv64 != KTIME_MAX)
		return false;
	ctx->moffs = ktime_get_monotonic_offset();
	return true;
}