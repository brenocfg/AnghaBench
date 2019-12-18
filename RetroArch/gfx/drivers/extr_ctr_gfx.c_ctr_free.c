#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* buffer; } ;
struct TYPE_9__ {TYPE_5__* frame_coords; TYPE_5__* texture_swizzled; TYPE_5__* texture_linear; } ;
struct TYPE_7__ {int /*<<< orphan*/  left; } ;
struct TYPE_8__ {TYPE_1__ top; } ;
struct TYPE_11__ {TYPE_4__ vertex_cache; struct TYPE_11__* empty_framebuffer; TYPE_3__ menu; struct TYPE_11__* frame_coords; struct TYPE_11__* texture_swizzled; struct TYPE_11__* texture_linear; struct TYPE_11__* display_list; TYPE_2__ drawbuffers; int /*<<< orphan*/  dvlb; int /*<<< orphan*/  shader; int /*<<< orphan*/  lcd_aptHook; } ;
typedef  TYPE_5__ ctr_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  DVLB_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSPGPU_EVENT_VBlank0 ; 
 int /*<<< orphan*/  aptUnhook (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfxExit () ; 
 int /*<<< orphan*/  gspSetEventCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  linearFree (TYPE_5__*) ; 
 int /*<<< orphan*/  shaderProgramFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vramFree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctr_free(void* data)
{
   ctr_video_t* ctr = (ctr_video_t*)data;

   if (!ctr)
      return;

   aptUnhook(&ctr->lcd_aptHook);
   gspSetEventCallback(GSPGPU_EVENT_VBlank0, NULL, NULL, true);
   shaderProgramFree(&ctr->shader);
   DVLB_Free(ctr->dvlb);
   vramFree(ctr->drawbuffers.top.left);
   linearFree(ctr->display_list);
   linearFree(ctr->texture_linear);
   linearFree(ctr->texture_swizzled);
   linearFree(ctr->frame_coords);
   linearFree(ctr->menu.texture_linear);
   linearFree(ctr->menu.texture_swizzled);
   linearFree(ctr->menu.frame_coords);
   linearFree(ctr->empty_framebuffer);
   linearFree(ctr->vertex_cache.buffer);
   linearFree(ctr);
#if 0
   gfxExit();
#endif
}