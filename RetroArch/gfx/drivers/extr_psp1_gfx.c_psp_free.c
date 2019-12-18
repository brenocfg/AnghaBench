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
struct TYPE_3__ {void* dList; void* frame; scalar_t__ frame_coords; } ;
struct TYPE_4__ {void* main_dList; void* frame_dList; TYPE_1__ menu; scalar_t__ frame_coords; } ;
typedef  TYPE_2__ psp1_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  GU_FALSE ; 
 int /*<<< orphan*/  PSP_VBLANK_INT ; 
 void* TO_CACHED_PTR (scalar_t__) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  sceDisplayWaitVblankStart () ; 
 int /*<<< orphan*/  sceGuDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuTerm () ; 
 int /*<<< orphan*/  sceKernelDisableSubIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceKernelReleaseSubIntrHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void psp_free(void *data)
{
   psp1_video_t *psp = (psp1_video_t*)data;

   if(!(psp) || !(psp->main_dList))
      return;

   sceDisplayWaitVblankStart();
   sceGuDisplay(GU_FALSE);
   sceGuTerm();

   if (psp->main_dList)
      free(psp->main_dList);
   if (psp->frame_dList)
      free(psp->frame_dList);
   if (psp->frame_coords)
      free(TO_CACHED_PTR(psp->frame_coords));
   if (psp->menu.frame_coords)
      free(TO_CACHED_PTR(psp->menu.frame_coords));
   if (psp->menu.dList)
      free(psp->menu.dList);
   if (psp->menu.frame)
      free(psp->menu.frame);

   free(data);

   sceKernelDisableSubIntr(PSP_VBLANK_INT, 0);
   sceKernelReleaseSubIntrHandler(PSP_VBLANK_INT,0);
}