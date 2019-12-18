#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {void* bounds; } ;
typedef  TYPE_2__ view_t ;
typedef  int /*<<< orphan*/  video_layout_orientation_t ;
typedef  int /*<<< orphan*/  video_layout_color_t ;
typedef  void* video_layout_bounds_t ;
typedef  int /*<<< orphan*/  scope_t ;
struct TYPE_27__ {int /*<<< orphan*/ * name; struct TYPE_27__* next; struct TYPE_27__* children; } ;
typedef  TYPE_3__ rxml_node_t ;
typedef  int /*<<< orphan*/  layer_t ;
struct TYPE_28__ {int i_raw; int components_count; void* bounds; TYPE_1__* components; void* i_mask; void* i_bind; void* o_bind; } ;
typedef  TYPE_4__ element_t ;
struct TYPE_25__ {int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  VIDEO_LAYOUT_ROT0 ; 
 void* bounds_union (void**,void**) ; 
 int /*<<< orphan*/  color_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  element_apply_orientation (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  element_copy (TYPE_4__*,TYPE_4__*) ; 
 void* get_int (int /*<<< orphan*/ *) ; 
 TYPE_4__* layer_add_element (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_param (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  load_screen (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*) ; 
 void* make_bounds () ; 
 int /*<<< orphan*/  make_color_white () ; 
 int /*<<< orphan*/  merge_group (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* parse_bounds (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  parse_color (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  parse_orientation (int /*<<< orphan*/ *,TYPE_3__*) ; 
 char* rxml_node_attrib (TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * scope_eval (int /*<<< orphan*/ *,char const*) ; 
 TYPE_4__* scope_find_element (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* scope_find_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scope_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scope_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scope_repeat (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 void* video_layout_io_find (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  view_deinit (TYPE_2__*) ; 
 int /*<<< orphan*/ * view_emplace_layer (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  view_init (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool load_view(scope_t *scope, view_t *view, rxml_node_t *node, bool is_named)
{
   bool result, has_bounds;
   rxml_node_t *n;
   rxml_node_t *o;
   int i;

   if (is_named)
   {
      const char *name;

      if (!(name = rxml_node_attrib(node, "name")))
      {
         RARCH_LOG("video_layout: <view> is missing 'name' attribute\n");
         return false;
      }

      view_init(view, scope_eval(scope, name));
   }

   result     = true;
   has_bounds = false;

   for (n = node->children; n; n = n->next)
   {
      video_layout_color_t       n_color;
      video_layout_bounds_t      n_bounds;
      video_layout_orientation_t n_orient;

      if (strcmp(n->name, "param") == 0)
      {
         if (!load_param(scope, n, true))
            result = false;
         continue;
      }

      else if (strcmp(n->name, "bounds") == 0)
      {
         view->bounds = parse_bounds(scope, n);
         has_bounds = true;
         continue;
      }

      n_color  = make_color_white();
      n_bounds = make_bounds();
      n_orient = VIDEO_LAYOUT_ROT0;

      for (o = n->children; o; o = o->next)
      {
         if (strcmp(o->name, "color") == 0)
            n_color = parse_color(scope, o);

         else if (strcmp(o->name, "bounds") == 0)
            n_bounds = parse_bounds(scope, o);

         else if (strcmp(o->name, "orientation") == 0)
            n_orient = parse_orientation(scope, o);
      }

      if (strcmp(n->name, "group") == 0)
      {
         const char *ref;
         if ((ref = rxml_node_attrib(n, "ref")))
         {
            view_t *group;
            if ((group = scope_find_group(scope, scope_eval(scope, ref))))
            {
               merge_group(scope, view, group, has_bounds, n_bounds, n_orient, n_color);
            }
            else
            {
               RARCH_LOG("video_layout: group \"%s\" is missing\n", scope_eval(scope, ref));
               result = false;
            }
         }
         else
         {
            RARCH_LOG("video_layout: <group> is missing 'ref' attribute\n");
            result = false;
         }
      }

      else if (strcmp(n->name, "repeat") == 0)
      {
         const char *count_s;
         int count;

         if (!(count_s = rxml_node_attrib(n, "count")))
         {
            RARCH_LOG("video_layout: <repeat> is missing 'count' attribute\n");
            result = false;
            continue;
         }

         count = get_int(scope_eval(scope, count_s));

         scope_push(scope);

         for (o = n->children; o; o = o->next)
         {
            if (strcmp(o->name, "param") == 0)
            {
               if (!load_param(scope, o, true))
                  result = false;
            }
         }

         for (i = 0; i < count; ++i)
         {
            view_t rep;
            view_init(&rep, NULL);

            if (!load_view(scope, &rep, n, false))
               result = false;

            merge_group(scope, view, &rep, has_bounds, n_bounds, n_orient, n_color);

            view_deinit(&rep);

            scope_repeat(scope);
         }

         scope_pop(scope);
      }

      else /* element */
      {
         layer_t *layer;
         element_t *elem;

         layer = view_emplace_layer(view, n->name);
         elem = layer_add_element(layer);

         if (strcmp(n->name, "screen") == 0)
         {
            if (!load_screen(scope, elem, n))
               result = false;
         }
         else
         {
            const char *elem_name;
            const char *attr;

            if ((elem_name = rxml_node_attrib(n, "element")))
            {
               element_t *elem_src;
               if ((elem_src = scope_find_element(scope, elem_name)))
               {
                  element_copy(elem, elem_src);

                  if ((attr = rxml_node_attrib(n, "name")))
                     elem->o_bind = video_layout_io_find(scope_eval(scope, attr));

                  if ((attr = rxml_node_attrib(n, "inputtag")))
                     elem->i_bind = video_layout_io_find(scope_eval(scope, attr));

                  if ((attr = rxml_node_attrib(n, "inputmask")))
                     elem->i_mask = get_int(scope_eval(scope, attr));

                  if ((attr = rxml_node_attrib(n, "inputraw")))
                     elem->i_raw = get_int(scope_eval(scope, attr)) ? true : false;
               }
               else
               {
                  RARCH_LOG("video_layout: element \"%s\" is missing\n", scope_eval(scope, elem_name));
                  result = false;
               }
            }
            else
            {
               RARCH_LOG("video_layout: <%s> is missing 'element' attribute\n", n->name);
               result = false;
            }
         }

         for (i = 0; i < elem->components_count; ++i)
            color_mod(&elem->components->color, &n_color);

         elem->bounds = n_bounds;

         if (n_orient)
            element_apply_orientation(elem, n_orient);

         if (!has_bounds)
            view->bounds = bounds_union(&view->bounds, &elem->bounds);
      }
   }

   return result;
}