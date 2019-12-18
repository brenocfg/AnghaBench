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
struct TYPE_3__ {int state; int o_bind; int i_bind; int i_mask; int i_raw; int components_count; int /*<<< orphan*/ * components; int /*<<< orphan*/  render_bounds; int /*<<< orphan*/  bounds; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ element_t ;
typedef  int /*<<< orphan*/  component_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  init_string (char const*) ; 
 int /*<<< orphan*/  make_bounds () ; 
 int /*<<< orphan*/  make_bounds_unit () ; 

void element_init(element_t *elem, const char *name, int components_count)
{
   elem->name   = init_string(name);
   elem->state  = -1;
   elem->o_bind = -1;
   elem->i_bind = -1;
   elem->i_mask = -1;
   elem->i_raw  = false;

   elem->bounds = make_bounds();
   elem->render_bounds = make_bounds_unit();

   elem->components = (component_t*)(components_count > 0 ?
         calloc(components_count, sizeof(component_t)) : NULL);
   elem->components_count = components_count;
}