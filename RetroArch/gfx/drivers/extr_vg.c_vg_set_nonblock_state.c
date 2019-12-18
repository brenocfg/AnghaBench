#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ctx_data; TYPE_1__* ctx_driver; } ;
typedef  TYPE_3__ vg_t ;
struct TYPE_7__ {scalar_t__ video_adaptive_vsync; } ;
struct TYPE_9__ {TYPE_2__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* swap_interval ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_CTX_FLAGS_ADAPTIVE_VSYNC ; 
 TYPE_4__* config_get_ptr () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ video_driver_test_all_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vg_set_nonblock_state(void *data, bool state)
{
   vg_t *vg     = (vg_t*)data;
   int interval = state ? 0 : 1;

   if (vg->ctx_driver && vg->ctx_driver->swap_interval)
   {
      settings_t *settings                   = config_get_ptr();
      bool adaptive_vsync_enabled            = video_driver_test_all_flags(
            GFX_CTX_FLAGS_ADAPTIVE_VSYNC) && settings->bools.video_adaptive_vsync;
      if (adaptive_vsync_enabled && interval == 1)
         interval = -1;
      vg->ctx_driver->swap_interval(vg->ctx_data, interval);
   }
}