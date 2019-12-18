#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int aspect; } ;
struct TYPE_5__ {TYPE_1__ displayMode; } ;
typedef  TYPE_2__ CellVideoOutState ;

/* Variables and functions */
#define  CELL_VIDEO_OUT_ASPECT_16_9 129 
#define  CELL_VIDEO_OUT_ASPECT_4_3 128 
 int /*<<< orphan*/  CELL_VIDEO_OUT_PRIMARY ; 
 int /*<<< orphan*/  cellVideoOutGetState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static float gfx_ctx_ps3_get_aspect_ratio(void *data)
{
   CellVideoOutState videoState;

   cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &videoState);

   switch (videoState.displayMode.aspect)
   {
      case CELL_VIDEO_OUT_ASPECT_4_3:
         return 4.0f/3.0f;
      case CELL_VIDEO_OUT_ASPECT_16_9:
         break;
   }

   return 16.0f/9.0f;
}