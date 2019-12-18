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
struct TYPE_3__ {unsigned int components_count; int /*<<< orphan*/ * name; int /*<<< orphan*/ * components; } ;
typedef  TYPE_1__ element_t ;

/* Variables and functions */
 int /*<<< orphan*/  component_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void element_deinit(element_t *elem)
{
   unsigned i;

   for (i = 0; i < elem->components_count; ++i)
      component_deinit(&elem->components[i]);
   free(elem->components);

   free(elem->name);
}