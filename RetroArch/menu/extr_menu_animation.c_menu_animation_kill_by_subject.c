#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tween {float* subject; int deleted; } ;
struct TYPE_4__ {unsigned int count; scalar_t__ data; } ;
typedef  TYPE_1__ menu_animation_ctx_subject_t ;
struct TYPE_5__ {int pending_deletes; int /*<<< orphan*/  list; scalar_t__ in_update; } ;

/* Variables and functions */
 TYPE_3__ anim ; 
 unsigned int da_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_delete (int /*<<< orphan*/ ,unsigned int) ; 
 struct tween* da_getptr (int /*<<< orphan*/ ,unsigned int) ; 

void menu_animation_kill_by_subject(menu_animation_ctx_subject_t *subject)
{
   unsigned i, j,  killed = 0;
   float            **sub = (float**)subject->data;

   for (i = 0; i < da_count(anim.list) && killed < subject->count; ++i)
   {
      struct tween *t = da_getptr(anim.list, i);
      if (!t)
         continue;

      for (j = 0; j < subject->count; ++j)
      {
         if (t->subject != sub[j])
            continue;

         if (anim.in_update)
         {
            t->deleted = true;
            anim.pending_deletes = true;
         }
         else
         {
            da_delete(anim.list, i);
            --i;
         }

         killed++;
         break;
      }
   }
}