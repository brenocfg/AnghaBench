#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rarch_dir_list {scalar_t__ ptr; int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dir_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dir_shader_list ; 

__attribute__((used)) static bool dir_free_shader(void)
{
   struct rarch_dir_list *dir_list =
      (struct rarch_dir_list*)&dir_shader_list;

   dir_list_free(dir_list->list);
   dir_list->list = NULL;
   dir_list->ptr  = 0;

   return true;
}