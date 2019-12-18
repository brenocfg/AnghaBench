#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct i915_hw_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DEFAULT_CONTEXT_ID ; 
 int /*<<< orphan*/  do_destroy (struct i915_hw_context*) ; 

__attribute__((used)) static int context_idr_cleanup(int id, void *p, void *data)
{
	struct i915_hw_context *ctx = p;

	BUG_ON(id == DEFAULT_CONTEXT_ID);

	do_destroy(ctx);

	return 0;
}