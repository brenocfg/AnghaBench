#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_8__* shader_preset; TYPE_4__* luts; TYPE_7__* pass; } ;
typedef  TYPE_5__ wiiu_video_t ;
struct TYPE_15__ {unsigned int passes; unsigned int luts; } ;
struct TYPE_9__ {int /*<<< orphan*/ * image; } ;
struct TYPE_10__ {TYPE_1__ surface; } ;
struct TYPE_14__ {TYPE_2__ texture; scalar_t__ mem1; int /*<<< orphan*/ ** ps_ubos; int /*<<< orphan*/ ** vs_ubos; int /*<<< orphan*/  gfd; } ;
struct TYPE_11__ {int /*<<< orphan*/ * image; } ;
struct TYPE_12__ {TYPE_3__ surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM1_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEM2_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_8__*) ; 
 int /*<<< orphan*/  gfd_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wiiu_free_shader_preset(wiiu_video_t *wiiu)
{
   unsigned i;
   if (!wiiu->shader_preset)
      return;

   for (i = 0; i < wiiu->shader_preset->passes; i++)
   {
      gfd_free(wiiu->pass[i].gfd);
      MEM2_free(wiiu->pass[i].vs_ubos[0]);
      MEM2_free(wiiu->pass[i].vs_ubos[1]);
      MEM2_free(wiiu->pass[i].ps_ubos[0]);
      MEM2_free(wiiu->pass[i].ps_ubos[1]);
      if(wiiu->pass[i].mem1)
         MEM1_free(wiiu->pass[i].texture.surface.image);
      else
         MEM2_free(wiiu->pass[i].texture.surface.image);
   }

   memset(wiiu->pass, 0, sizeof(wiiu->pass));

   for (i = 0; i < wiiu->shader_preset->luts; i++)
   {
      MEM2_free(wiiu->luts[i].surface.image);
      wiiu->luts[i].surface.image = NULL;
   }

   free(wiiu->shader_preset);
   wiiu->shader_preset = NULL;
}