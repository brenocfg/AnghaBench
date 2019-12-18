#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  settings_t ;
struct TYPE_7__ {int need_compute; } ;
typedef  TYPE_1__ materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/ * config_get_ptr () ; 
 int /*<<< orphan*/  materialui_set_landscape_optimisations_enable (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  materialui_set_list_view_type (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  materialui_set_secondary_thumbnail_enable (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  materialui_set_thumbnail_dimensions (TYPE_1__*) ; 

__attribute__((used)) static void materialui_update_list_view(materialui_handle_t *mui)
{
   settings_t *settings = config_get_ptr();

   if (!settings)
      return;

   materialui_set_list_view_type(mui, settings);
   materialui_set_landscape_optimisations_enable(mui, settings);
   materialui_set_thumbnail_dimensions(mui);
   materialui_set_secondary_thumbnail_enable(mui, settings);

   mui->need_compute = true;
}