#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  range_mod; int /*<<< orphan*/  alpha_mod; int /*<<< orphan*/  normalized; } ;
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct overlay {size_t pos; size_t pos_increment; size_t size; TYPE_2__ config; TYPE_1__ image; int /*<<< orphan*/ * descs; } ;
struct TYPE_12__ {scalar_t__ state; } ;
typedef  TYPE_3__ retro_task_t ;
struct TYPE_13__ {size_t pos; size_t size; int loading_status; void* state; struct overlay* overlays; } ;
typedef  TYPE_4__ overlay_loader_t ;

/* Variables and functions */
#define  OVERLAY_IMAGE_TRANSFER_BUSY 134 
#define  OVERLAY_IMAGE_TRANSFER_DESC_DONE 133 
#define  OVERLAY_IMAGE_TRANSFER_DESC_IMAGE_ITERATE 132 
#define  OVERLAY_IMAGE_TRANSFER_DESC_ITERATE 131 
#define  OVERLAY_IMAGE_TRANSFER_DONE 130 
#define  OVERLAY_IMAGE_TRANSFER_ERROR 129 
#define  OVERLAY_IMAGE_TRANSFER_NONE 128 
 void* OVERLAY_STATUS_DEFERRED_ERROR ; 
 void* OVERLAY_STATUS_DEFERRED_LOADING_RESOLVE ; 
 int /*<<< orphan*/  RARCH_ERR (char*,unsigned int) ; 
 int /*<<< orphan*/  task_overlay_image_done (struct overlay*) ; 
 int /*<<< orphan*/  task_overlay_load_desc (TYPE_4__*,int /*<<< orphan*/ *,struct overlay*,size_t,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_overlay_load_desc_image (TYPE_4__*,int /*<<< orphan*/ *,struct overlay*,size_t,unsigned int) ; 
 int /*<<< orphan*/  task_overlay_resolve_iterate (TYPE_3__*) ; 
 int /*<<< orphan*/  task_set_cancelled (TYPE_3__*,int) ; 

__attribute__((used)) static void task_overlay_deferred_loading(retro_task_t *task)
{
   size_t i                  = 0;
   overlay_loader_t *loader  = (overlay_loader_t*)task->state;
   struct overlay *overlay   = &loader->overlays[loader->pos];
   bool not_done             = loader->pos < loader->size;

   if (!not_done)
   {
      loader->state = OVERLAY_STATUS_DEFERRED_LOADING_RESOLVE;
      return;
   }

   switch (loader->loading_status)
   {
      case OVERLAY_IMAGE_TRANSFER_NONE:
      case OVERLAY_IMAGE_TRANSFER_BUSY:
         loader->loading_status = OVERLAY_IMAGE_TRANSFER_DONE;
#if 0
         break;
#endif
      case OVERLAY_IMAGE_TRANSFER_DONE:
         task_overlay_image_done(&loader->overlays[loader->pos]);
         loader->loading_status = OVERLAY_IMAGE_TRANSFER_DESC_IMAGE_ITERATE;
         loader->overlays[loader->pos].pos = 0;
         break;
      case OVERLAY_IMAGE_TRANSFER_DESC_IMAGE_ITERATE:
         for (i = 0; i < overlay->pos_increment; i++)
         {
            if (overlay->pos < overlay->size)
            {
               task_overlay_load_desc_image(loader,
                     &overlay->descs[overlay->pos], overlay,
                     loader->pos, (unsigned)overlay->pos);
            }
            else
            {
               overlay->pos       = 0;
               loader->loading_status = OVERLAY_IMAGE_TRANSFER_DESC_ITERATE;
               break;
            }

         }
         break;
      case OVERLAY_IMAGE_TRANSFER_DESC_ITERATE:
         for (i = 0; i < overlay->pos_increment; i++)
         {
            if (overlay->pos < overlay->size)
            {
               if (!task_overlay_load_desc(loader,
                        &overlay->descs[overlay->pos], overlay,
                        loader->pos, (unsigned)overlay->pos,
                        overlay->image.width, overlay->image.height,
                        overlay->config.normalized,
                        overlay->config.alpha_mod, overlay->config.range_mod))
               {
                  RARCH_ERR("[Overlay]: Failed to load overlay descs for overlay #%u.\n",
                        (unsigned)overlay->pos);
                  task_set_cancelled(task, true);
                  loader->state   = OVERLAY_STATUS_DEFERRED_ERROR;
                  break;
               }
            }
            else
            {
               overlay->pos       = 0;
               loader->loading_status = OVERLAY_IMAGE_TRANSFER_DESC_DONE;
               break;
            }
         }
         break;
      case OVERLAY_IMAGE_TRANSFER_DESC_DONE:
         if (loader->pos == 0)
            task_overlay_resolve_iterate(task);

         loader->pos += 1;
         loader->loading_status = OVERLAY_IMAGE_TRANSFER_NONE;
         break;
      case OVERLAY_IMAGE_TRANSFER_ERROR:
         task_set_cancelled(task, true);
         loader->state   = OVERLAY_STATUS_DEFERRED_ERROR;
         break;
   }
}