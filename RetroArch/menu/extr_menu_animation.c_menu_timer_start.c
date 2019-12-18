#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  float menu_timer_t ;
struct TYPE_5__ {int /*<<< orphan*/  userdata; int /*<<< orphan*/  cb; int /*<<< orphan*/  duration; } ;
typedef  TYPE_1__ menu_timer_ctx_entry_t ;
typedef  uintptr_t menu_animation_ctx_tag ;
struct TYPE_6__ {uintptr_t tag; float target_value; float* subject; int /*<<< orphan*/  userdata; int /*<<< orphan*/  cb; int /*<<< orphan*/  duration; int /*<<< orphan*/  easing_enum; } ;
typedef  TYPE_2__ menu_animation_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_LINEAR ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_timer_kill (float*) ; 

void menu_timer_start(menu_timer_t *timer, menu_timer_ctx_entry_t *timer_entry)
{
   menu_animation_ctx_entry_t entry;
   menu_animation_ctx_tag tag = (uintptr_t) timer;

   menu_timer_kill(timer);

   *timer = 0.0f;

   entry.easing_enum    = EASING_LINEAR;
   entry.tag            = tag;
   entry.duration       = timer_entry->duration;
   entry.target_value   = 1.0f;
   entry.subject        = timer;
   entry.cb             = timer_entry->cb;
   entry.userdata       = timer_entry->userdata;

   menu_animation_push(&entry);
}