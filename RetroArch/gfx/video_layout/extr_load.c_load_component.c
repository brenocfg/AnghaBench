#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* video_layout_text_align_t ;
typedef  int /*<<< orphan*/  scope_t ;
struct TYPE_17__ {int /*<<< orphan*/  name; struct TYPE_17__* next; struct TYPE_17__* children; } ;
typedef  TYPE_5__ rxml_node_t ;
struct TYPE_15__ {void* align; void* max_state; void* digits; } ;
struct TYPE_14__ {void* align; int /*<<< orphan*/  string; } ;
struct TYPE_13__ {int /*<<< orphan*/  alpha_file; int /*<<< orphan*/  file; } ;
struct TYPE_16__ {TYPE_3__ counter; TYPE_2__ text; TYPE_1__ image; } ;
struct TYPE_18__ {int type; TYPE_4__ attr; int /*<<< orphan*/  color; int /*<<< orphan*/  bounds; void* enabled_state; } ;
typedef  TYPE_6__ component_t ;
typedef  scalar_t__ comp_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ) ; 
#define  VIDEO_LAYOUT_C_COUNTER 144 
#define  VIDEO_LAYOUT_C_DISK 143 
#define  VIDEO_LAYOUT_C_DOTMATRIX_H5 142 
#define  VIDEO_LAYOUT_C_DOTMATRIX_H8 141 
#define  VIDEO_LAYOUT_C_DOTMATRIX_X1 140 
#define  VIDEO_LAYOUT_C_IMAGE 139 
#define  VIDEO_LAYOUT_C_LED_14 138 
#define  VIDEO_LAYOUT_C_LED_14_SC 137 
#define  VIDEO_LAYOUT_C_LED_16 136 
#define  VIDEO_LAYOUT_C_LED_16_SC 135 
#define  VIDEO_LAYOUT_C_LED_7 134 
#define  VIDEO_LAYOUT_C_LED_8_GTS1 133 
#define  VIDEO_LAYOUT_C_RECT 132 
#define  VIDEO_LAYOUT_C_REEL 131 
#define  VIDEO_LAYOUT_C_SCREEN 130 
#define  VIDEO_LAYOUT_C_TEXT 129 
#define  VIDEO_LAYOUT_C_UNKNOWN 128 
 scalar_t__ comp_type_from_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  component_init (TYPE_6__*,scalar_t__) ; 
 void* get_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_bounds (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  parse_color (int /*<<< orphan*/ *,TYPE_5__*) ; 
 char* rxml_node_attrib (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  scope_eval (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool load_component(scope_t *scope, component_t *comp, rxml_node_t *node)
{
   const char *state;
   const char *attr;
   rxml_node_t *n;
   comp_type_t type = comp_type_from_str(node->name);
   bool      result = true;

   if (type == VIDEO_LAYOUT_C_UNKNOWN)
   {
      RARCH_LOG("video_layout: invalid component <%s />\n", node->name);
      return false;
   }

   component_init(comp, type);

   if ((state = rxml_node_attrib(node, "state")))
      comp->enabled_state = get_int(scope_eval(scope, state));

   for (n = node->children; n; n = n->next)
   {
      if (strcmp(n->name, "bounds") == 0)
         comp->bounds = parse_bounds(scope, n);

      else if (strcmp(n->name, "color") == 0)
         comp->color = parse_color(scope, n);
   }

   switch (comp->type)
   {
      case VIDEO_LAYOUT_C_UNKNOWN:
         break;
      case VIDEO_LAYOUT_C_SCREEN:
         break;
      case VIDEO_LAYOUT_C_RECT:
         break;
      case VIDEO_LAYOUT_C_DISK:
         break;
      case VIDEO_LAYOUT_C_IMAGE:
         {
            if (!(attr = rxml_node_attrib(node, "file")))
            {
               RARCH_LOG("video_layout: invalid component <%s />, missing 'file' attribute\n", node->name);
               result = false;
            }
            set_string(&comp->attr.image.file, scope_eval(scope, attr));

            if ((attr = rxml_node_attrib(node, "alphafile")))
               set_string(&comp->attr.image.alpha_file, scope_eval(scope, attr));
         }
         break;
      case VIDEO_LAYOUT_C_TEXT:
         {
            if (!(attr = rxml_node_attrib(node, "string")))
            {
               RARCH_LOG("video_layout: invalid component <%s />, missing 'string' attribute\n", node->name);
               result = false;
            }
            set_string(&comp->attr.text.string, scope_eval(scope, attr));

            if ((attr = rxml_node_attrib(node, "align")))
               comp->attr.text.align = (video_layout_text_align_t)get_int(scope_eval(scope, attr));
         }
         break;
      case VIDEO_LAYOUT_C_COUNTER:
         {
            if ((attr = rxml_node_attrib(node, "digits")))
               comp->attr.counter.digits = get_int(scope_eval(scope, attr));

            if ((attr = rxml_node_attrib(node, "maxstate")))
               comp->attr.counter.max_state = get_int(scope_eval(scope, attr));

            if ((attr = rxml_node_attrib(node, "align")))
               comp->attr.counter.align = (video_layout_text_align_t)get_int(scope_eval(scope, attr));
         }
         break;
      case VIDEO_LAYOUT_C_DOTMATRIX_X1:
         break;
      case VIDEO_LAYOUT_C_DOTMATRIX_H5:
         break;
      case VIDEO_LAYOUT_C_DOTMATRIX_H8:
         break;
      case VIDEO_LAYOUT_C_LED_7:
         break;
      case VIDEO_LAYOUT_C_LED_8_GTS1:
         break;
      case VIDEO_LAYOUT_C_LED_14:
         break;
      case VIDEO_LAYOUT_C_LED_14_SC:
         break;
      case VIDEO_LAYOUT_C_LED_16:
         break;
      case VIDEO_LAYOUT_C_LED_16_SC:
         break;
      case VIDEO_LAYOUT_C_REEL:
         break;
   }

   return result;
}