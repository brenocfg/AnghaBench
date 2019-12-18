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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  pixel_t ;
struct TYPE_4__ {int* draw_finished; scalar_t__* need_draw; } ;
struct TYPE_3__ {int draw_finished; scalar_t__ need_draw; } ;

/* Variables and functions */
 int TitanInit () ; 
 int /*<<< orphan*/  VIDSoftSetupGL () ; 
 int /*<<< orphan*/  VidsoftNbg0Thread ; 
 int /*<<< orphan*/  VidsoftNbg1Thread ; 
 int /*<<< orphan*/  VidsoftNbg2Thread ; 
 int /*<<< orphan*/  VidsoftNbg3Thread ; 
 int /*<<< orphan*/  VidsoftRbg0Thread ; 
 int /*<<< orphan*/  VidsoftSpriteThread ; 
 int /*<<< orphan*/  VidsoftVdp1Thread ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_LAYER_NBG0 ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_LAYER_NBG1 ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_LAYER_NBG2 ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_LAYER_NBG3 ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_LAYER_RBG0 ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_LAYER_SPRITE ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_VDP1 ; 
 int /*<<< orphan*/  YabThreadStart (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/ * dispbuffer ; 
 int rbg0width ; 
 int /*<<< orphan*/ * vdp1backframebuffer ; 
 int /*<<< orphan*/ ** vdp1framebuffer ; 
 int /*<<< orphan*/ * vdp1frontframebuffer ; 
 int vdp2height ; 
 int vdp2width ; 
 TYPE_2__ vidsoft_thread_context ; 
 TYPE_1__ vidsoft_vdp1_thread_context ; 

int VIDSoftInit(void)
{
   int i;

   if (TitanInit() == -1)
      return -1;

   if ((dispbuffer = (pixel_t *)calloc(sizeof(pixel_t), 704 * 512)) == NULL)
      return -1;

   // Initialize VDP1 framebuffer 1
   if ((vdp1framebuffer[0] = (u8 *)calloc(sizeof(u8), 0x40000)) == NULL)
      return -1;

   // Initialize VDP1 framebuffer 2
   if ((vdp1framebuffer[1] = (u8 *)calloc(sizeof(u8), 0x40000)) == NULL)
      return -1;

   vdp1backframebuffer = vdp1framebuffer[0];
   vdp1frontframebuffer = vdp1framebuffer[1];
   rbg0width = vdp2width = 320;
   vdp2height = 224;

#ifdef USE_OPENGL
   VIDSoftSetupGL();
#endif

   for (i = 0; i < 6; i++)
   {
      vidsoft_thread_context.draw_finished[i] = 1;
      vidsoft_thread_context.need_draw[i] = 0;
   }

   vidsoft_vdp1_thread_context.need_draw = 0;
   vidsoft_vdp1_thread_context.draw_finished = 1;
   YabThreadStart(YAB_THREAD_VIDSOFT_VDP1, VidsoftVdp1Thread, 0);

   YabThreadStart(YAB_THREAD_VIDSOFT_LAYER_RBG0, VidsoftRbg0Thread, 0);
   YabThreadStart(YAB_THREAD_VIDSOFT_LAYER_NBG0, VidsoftNbg0Thread, 0);
   YabThreadStart(YAB_THREAD_VIDSOFT_LAYER_NBG1, VidsoftNbg1Thread, 0);
   YabThreadStart(YAB_THREAD_VIDSOFT_LAYER_NBG2, VidsoftNbg2Thread, 0);
   YabThreadStart(YAB_THREAD_VIDSOFT_LAYER_NBG3, VidsoftNbg3Thread, 0);
   YabThreadStart(YAB_THREAD_VIDSOFT_LAYER_SPRITE, VidsoftSpriteThread, 0);

   return 0;
}