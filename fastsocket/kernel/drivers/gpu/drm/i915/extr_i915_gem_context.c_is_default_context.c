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
struct i915_hw_context {TYPE_1__* ring; } ;
struct TYPE_2__ {struct i915_hw_context* default_context; } ;

/* Variables and functions */

__attribute__((used)) static inline bool is_default_context(struct i915_hw_context *ctx)
{
	return (ctx == ctx->ring->default_context);
}