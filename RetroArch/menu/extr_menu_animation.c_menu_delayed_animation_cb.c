#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ menu_delayed_animation_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  menu_animation_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void menu_delayed_animation_cb(void *userdata)
{
   menu_delayed_animation_t *delayed_animation = (menu_delayed_animation_t*) userdata;

   menu_animation_push(&delayed_animation->entry);

   free(delayed_animation);
}