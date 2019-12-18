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
typedef  int /*<<< orphan*/  switch_ctx_data_t ;

/* Variables and functions */
#define  AppletOperationMode_Docked 129 
#define  AppletOperationMode_Handheld 128 
 int appletGetOperationMode () ; 

__attribute__((used)) static void switch_ctx_get_video_size(void *data,
                                      unsigned *width, unsigned *height)
{
   switch_ctx_data_t *ctx_nx = (switch_ctx_data_t *)data;

   switch (appletGetOperationMode())
      {
         default:
         case AppletOperationMode_Handheld:
            *width = 1280;
            *height = 720;
            break;
         case AppletOperationMode_Docked:
            *width = 1920;
            *height = 1080;
            break;
      }
}