#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_15__ {int /*<<< orphan*/  overlay_scale; int /*<<< orphan*/  overlay_opacity; int /*<<< orphan*/  overlay_enable; int /*<<< orphan*/  hide_in_menu; int /*<<< orphan*/  active; int /*<<< orphan*/  size; int /*<<< orphan*/  overlays; } ;
typedef  TYPE_2__ overlay_task_data_t ;
struct TYPE_16__ {int state; int /*<<< orphan*/  overlay_scale; int /*<<< orphan*/  overlay_opacity; int /*<<< orphan*/  overlay_enable; int /*<<< orphan*/  overlay_hide_in_menu; int /*<<< orphan*/  active; int /*<<< orphan*/  size; int /*<<< orphan*/  overlays; } ;
typedef  TYPE_3__ overlay_loader_t ;

/* Variables and functions */
#define  OVERLAY_STATUS_DEFERRED_DONE 133 
#define  OVERLAY_STATUS_DEFERRED_ERROR 132 
#define  OVERLAY_STATUS_DEFERRED_LOAD 131 
#define  OVERLAY_STATUS_DEFERRED_LOADING 130 
#define  OVERLAY_STATUS_DEFERRED_LOADING_RESOLVE 129 
#define  OVERLAY_STATUS_NONE 128 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  task_get_cancelled (TYPE_1__*) ; 
 scalar_t__ task_get_finished (TYPE_1__*) ; 
 int /*<<< orphan*/  task_overlay_deferred_load (TYPE_1__*) ; 
 int /*<<< orphan*/  task_overlay_deferred_loading (TYPE_1__*) ; 
 int /*<<< orphan*/  task_overlay_resolve_iterate (TYPE_1__*) ; 
 int /*<<< orphan*/  task_set_cancelled (TYPE_1__*,int) ; 
 int /*<<< orphan*/  task_set_data (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  task_set_finished (TYPE_1__*,int) ; 

__attribute__((used)) static void task_overlay_handler(retro_task_t *task)
{
   overlay_loader_t *loader  = (overlay_loader_t*)task->state;

   switch (loader->state)
   {
      case OVERLAY_STATUS_DEFERRED_LOADING:
         task_overlay_deferred_loading(task);
         break;
      case OVERLAY_STATUS_DEFERRED_LOAD:
         task_overlay_deferred_load(task);
         break;
      case OVERLAY_STATUS_DEFERRED_LOADING_RESOLVE:
         task_overlay_resolve_iterate(task);
         break;
      case OVERLAY_STATUS_DEFERRED_ERROR:
         task_set_cancelled(task, true);
         break;
      case OVERLAY_STATUS_DEFERRED_DONE:
      default:
      case OVERLAY_STATUS_NONE:
         task_set_finished(task, true);
         break;
   }

   if (task_get_finished(task) && !task_get_cancelled(task))
   {
      overlay_task_data_t *data = (overlay_task_data_t*)
         calloc(1, sizeof(*data));

      data->overlays        = loader->overlays;
      data->size            = loader->size;
      data->active          = loader->active;
      data->hide_in_menu    = loader->overlay_hide_in_menu;
      data->overlay_enable  = loader->overlay_enable;
      data->overlay_opacity = loader->overlay_opacity;
      data->overlay_scale   = loader->overlay_scale;

      task_set_data(task, data);
   }
}