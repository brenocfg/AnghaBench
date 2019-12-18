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
struct vino_channel_settings {size_t data_norm; } ;
struct TYPE_2__ {int /*<<< orphan*/  fps_max; } ;

/* Variables and functions */
 TYPE_1__* vino_data_norms ; 
 int /*<<< orphan*/  vino_set_framerate (struct vino_channel_settings*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vino_set_default_framerate(struct
					      vino_channel_settings *vcs)
{
	vino_set_framerate(vcs, vino_data_norms[vcs->data_norm].fps_max);
}