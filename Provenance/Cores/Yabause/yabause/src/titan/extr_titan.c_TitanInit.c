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
struct PixelData {int dummy; } ;
typedef  struct PixelData u32 ;
struct TYPE_4__ {int* draw_finished; scalar_t__* need_draw; } ;
struct TYPE_3__ {int inited; struct PixelData** linescreen; struct PixelData** vdp2framebuffer; struct PixelData* backscreen; } ;

/* Variables and functions */
 int /*<<< orphan*/  VidsoftPriorityThread0 ; 
 int /*<<< orphan*/  VidsoftPriorityThread1 ; 
 int /*<<< orphan*/  VidsoftPriorityThread2 ; 
 int /*<<< orphan*/  VidsoftPriorityThread3 ; 
 int /*<<< orphan*/  VidsoftPriorityThread4 ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_PRIORITY_0 ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_PRIORITY_1 ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_PRIORITY_2 ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_PRIORITY_3 ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_PRIORITY_4 ; 
 int /*<<< orphan*/  YabThreadStart (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memset (struct PixelData*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ priority_thread_context ; 
 TYPE_1__ tt_context ; 

int TitanInit()
{
   int i;

   if (! tt_context.inited)
   {
      for(i = 0;i < 6;i++)
      {
         if ((tt_context.vdp2framebuffer[i] = (struct PixelData *)calloc(sizeof(struct PixelData), 704 * 256)) == NULL)
            return -1;
      }

      /* linescreen 0 is not initialized as it's not used... */
      for(i = 1;i < 4;i++)
      {
         if ((tt_context.linescreen[i] = (u32 *)calloc(sizeof(u32), 512)) == NULL)
            return -1;
      }

      if ((tt_context.backscreen = (struct PixelData  *)calloc(sizeof(struct PixelData), 704 * 512)) == NULL)
         return -1;

      for (i = 0; i < 5; i++)
      {
         priority_thread_context.draw_finished[i] = 1;
         priority_thread_context.need_draw[i] = 0;
      }

      YabThreadStart(YAB_THREAD_VIDSOFT_PRIORITY_0, VidsoftPriorityThread0, NULL);
      YabThreadStart(YAB_THREAD_VIDSOFT_PRIORITY_1, VidsoftPriorityThread1, NULL);
      YabThreadStart(YAB_THREAD_VIDSOFT_PRIORITY_2, VidsoftPriorityThread2, NULL);
      YabThreadStart(YAB_THREAD_VIDSOFT_PRIORITY_3, VidsoftPriorityThread3, NULL);
      YabThreadStart(YAB_THREAD_VIDSOFT_PRIORITY_4, VidsoftPriorityThread4, NULL);

      tt_context.inited = 1;
   }

   for(i = 0;i < 6;i++)
      memset(tt_context.vdp2framebuffer[i], 0, sizeof(u32) * 704 * 256);

   for(i = 1;i < 4;i++)
      memset(tt_context.linescreen[i], 0, sizeof(u32) * 512);

   return 0;
}