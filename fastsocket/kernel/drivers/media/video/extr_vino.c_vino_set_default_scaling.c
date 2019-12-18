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
struct TYPE_2__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct vino_channel_settings {TYPE_1__ clipping; } ;

/* Variables and functions */
 int /*<<< orphan*/  vino_set_scaling (struct vino_channel_settings*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void vino_set_default_scaling(struct vino_channel_settings *vcs)
{
	vino_set_scaling(vcs, vcs->clipping.right - vcs->clipping.left,
			 vcs->clipping.bottom - vcs->clipping.top);
}