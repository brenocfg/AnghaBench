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
struct drm_i915_gem_execbuffer2 {int flags; int batch_start_offset; int batch_len; } ;

/* Variables and functions */
 int __I915_EXEC_UNKNOWN_FLAGS ; 

__attribute__((used)) static bool
i915_gem_check_execbuffer(struct drm_i915_gem_execbuffer2 *exec)
{
	if (exec->flags & __I915_EXEC_UNKNOWN_FLAGS)
		return false;

	return ((exec->batch_start_offset | exec->batch_len) & 0x7) == 0;
}