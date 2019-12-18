#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ctx_data; TYPE_1__* ctx_driver; } ;
typedef  TYPE_2__ network_video_t ;
typedef  int /*<<< orphan*/  gfx_ctx_size_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* check_window ) (int /*<<< orphan*/ ,int*,int*,unsigned int*,unsigned int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_CTL_IS_SHUTDOWN ; 
 int rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*,int*,unsigned int*,unsigned int*,int) ; 
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  video_driver_set_size (unsigned int*,unsigned int*) ; 

__attribute__((used)) static bool network_gfx_alive(void *data)
{
   gfx_ctx_size_t size_data;
   unsigned temp_width  = 0;
   unsigned temp_height = 0;
   bool quit            = false;
   bool resize          = false;
   bool is_shutdown     = rarch_ctl(RARCH_CTL_IS_SHUTDOWN, NULL);
   network_video_t *network       = (network_video_t*)data;

   /* Needed because some context drivers don't track their sizes */
   video_driver_get_size(&temp_width, &temp_height);

   network->ctx_driver->check_window(network->ctx_data,
            &quit, &resize, &temp_width, &temp_height, is_shutdown);

   if (temp_width != 0 && temp_height != 0)
      video_driver_set_size(&temp_width, &temp_height);

   return true;
}