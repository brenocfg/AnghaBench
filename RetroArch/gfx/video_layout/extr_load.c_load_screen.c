#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scope_t ;
typedef  int /*<<< orphan*/  rxml_node_t ;
struct TYPE_10__ {TYPE_4__* components; } ;
typedef  TYPE_3__ element_t ;
struct TYPE_9__ {int /*<<< orphan*/  index; } ;
struct TYPE_8__ {TYPE_2__ screen; } ;
struct TYPE_11__ {TYPE_1__ attr; int /*<<< orphan*/  bounds; } ;
typedef  TYPE_4__ component_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_LAYOUT_C_SCREEN ; 
 int /*<<< orphan*/  component_init (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  element_init (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bounds_unit () ; 
 char* rxml_node_attrib (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  scope_eval (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bool load_screen(scope_t *scope, element_t *elem, rxml_node_t *node)
{
   component_t *comp;
   const char *index = rxml_node_attrib(node, "index");

   element_init(elem, NULL, 1);
   comp = &elem->components[0];

   component_init(comp, VIDEO_LAYOUT_C_SCREEN);
   comp->bounds = make_bounds_unit();
   comp->attr.screen.index = get_int(scope_eval(scope, index));

   return true;
}