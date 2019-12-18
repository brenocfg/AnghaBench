#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* x; void* y; void* h; void* w; } ;
typedef  TYPE_1__ video_layout_bounds_t ;
typedef  int /*<<< orphan*/  scope_t ;
typedef  int /*<<< orphan*/  rxml_node_t ;

/* Variables and functions */
 void* get_dec (char const*) ; 
 TYPE_1__ make_bounds_unit () ; 
 int /*<<< orphan*/  rxml_node_attrib (int /*<<< orphan*/ *,char*) ; 
 char* scope_eval (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static video_layout_bounds_t parse_bounds(scope_t *scope, rxml_node_t *node)
{
   const char *prop;
   video_layout_bounds_t bounds = make_bounds_unit();

   if ((prop = scope_eval(scope, rxml_node_attrib(node, "x"))))       bounds.x = get_dec(prop);
   if ((prop = scope_eval(scope, rxml_node_attrib(node, "y"))))       bounds.y = get_dec(prop);
   if ((prop = scope_eval(scope, rxml_node_attrib(node, "width"))))   bounds.w = get_dec(prop);
   if ((prop = scope_eval(scope, rxml_node_attrib(node, "height"))))  bounds.h = get_dec(prop);

   if ((prop = scope_eval(scope, rxml_node_attrib(node, "left"))))    bounds.x = get_dec(prop);
   if ((prop = scope_eval(scope, rxml_node_attrib(node, "top"))))     bounds.y = get_dec(prop);
   if ((prop = scope_eval(scope, rxml_node_attrib(node, "right"))))   bounds.w = get_dec(prop) - bounds.x;
   if ((prop = scope_eval(scope, rxml_node_attrib(node, "bottom"))))  bounds.h = get_dec(prop) - bounds.y;

   return bounds;
}