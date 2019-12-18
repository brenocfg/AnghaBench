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
struct TYPE_2__ {void* menuTexture; void* coreTexture; int /*<<< orphan*/  gsGlobal; } ;
typedef  TYPE_1__ ps2_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_BLACK ; 
 int /*<<< orphan*/  deinitTexture (void*) ; 
 int /*<<< orphan*/  font_driver_free_osd () ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  gsKit_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsKit_deinit_global (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsKit_vram_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps2_gfx_free(void *data)
{
   ps2_video_t *ps2 = (ps2_video_t*)data;

   gsKit_clear(ps2->gsGlobal, GS_BLACK);
   gsKit_vram_clear(ps2->gsGlobal);

   font_driver_free_osd();

   deinitTexture(ps2->menuTexture);
   deinitTexture(ps2->coreTexture);

   free(ps2->menuTexture);
   free(ps2->coreTexture);

   gsKit_deinit_global(ps2->gsGlobal);

   free(data);
}