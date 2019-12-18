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
struct TYPE_5__ {int /*<<< orphan*/  x; int /*<<< orphan*/  label_alpha; int /*<<< orphan*/  alpha; } ;
typedef  TYPE_1__ stripes_node_t ;
struct TYPE_6__ {float target_value; uintptr_t tag; int /*<<< orphan*/ * subject; int /*<<< orphan*/ * cb; int /*<<< orphan*/  easing_enum; int /*<<< orphan*/  duration; } ;
typedef  TYPE_2__ menu_animation_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  STRIPES_DELAY ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_2__*) ; 

__attribute__((used)) static void stripes_push_animations(stripes_node_t *node,
      uintptr_t tag, float ia, float ix)
{
   menu_animation_ctx_entry_t anim_entry;

   anim_entry.duration     = STRIPES_DELAY;
   anim_entry.target_value = ia;
   anim_entry.subject      = &node->alpha;
   anim_entry.easing_enum  = EASING_OUT_QUAD;
   anim_entry.tag          = tag;
   anim_entry.cb           = NULL;

   menu_animation_push(&anim_entry);

   anim_entry.subject      = &node->label_alpha;

   menu_animation_push(&anim_entry);

   anim_entry.target_value = ix;
   anim_entry.subject      = &node->x;

   menu_animation_push(&anim_entry);
}