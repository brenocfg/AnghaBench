#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* closed_top; int /*<<< orphan*/  stack; int /*<<< orphan*/ * key; int /*<<< orphan*/ * plist; int /*<<< orphan*/  value; int /*<<< orphan*/  tag_stack; } ;
typedef  TYPE_1__ parse_data_t ;
typedef  scalar_t__ gpointer ;
typedef  void* gint64 ;
typedef  size_t gint ;
typedef  void* gdouble ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {size_t id; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  scalar_t__ GhbType ;
typedef  int /*<<< orphan*/  GMarkupParseContext ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ GHB_ARRAY ; 
 scalar_t__ GHB_DICT ; 
#define  P_ARRAY 136 
#define  P_DICT 135 
#define  P_FALSE 134 
#define  P_INTEGER 133 
#define  P_KEY 132 
#define  P_PLIST 131 
#define  P_REAL 130 
#define  P_STRING 129 
#define  P_TRUE 128 
 size_t TAG_MAP_SZ ; 
 void* TRUE ; 
 int /*<<< orphan*/  g_error (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_message (char*,size_t) ; 
 scalar_t__ g_queue_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_queue_peek_head (int /*<<< orphan*/ ) ; 
 scalar_t__ g_queue_pop_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_strdup (int /*<<< orphan*/ ) ; 
 void* g_strtod (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_warning (char*,...) ; 
 int /*<<< orphan*/  ghb_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_bool_value_new (void*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_double_value_new (void*) ; 
 int /*<<< orphan*/ * ghb_int_value_new (void*) ; 
 int /*<<< orphan*/ * ghb_string_value_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 scalar_t__ ghb_value_type (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* tag_map ; 

__attribute__((used)) static void
end_element(
    GMarkupParseContext *ctx,
    const gchar *name,
    gpointer ud,
    GError **error)
{
    parse_data_t *pd = (parse_data_t*)ud;
    gint id;
    union
    {
        gint id;
        gpointer pid;
    } start_id;
    gint ii;

    // Check to see if the first element found has been closed
    // If so, ignore any junk following it.
    if (pd->closed_top)
        return;

    for (ii = 0; ii < TAG_MAP_SZ; ii++)
    {
        if (strcmp(name, tag_map[ii].tag) == 0)
        {
            id = tag_map[ii].id;
            break;
        }
    }
    if (ii == TAG_MAP_SZ)
    {
        g_warning("Unrecognized start tag (%s)", name);
        return;
    }
    start_id.pid = g_queue_pop_head(pd->tag_stack);
    if (start_id.id != id)
        g_warning("start tag != end tag: (%s %d) %d", name, id, id);

    GhbValue *gval = NULL;
    GhbValue *current = g_queue_peek_head(pd->stack);
    GhbType gtype = 0;
    switch (id)
    {
        case P_PLIST:
        { // Ignore
        } break;
        case P_KEY:
        {
            if (pd->key) g_free(pd->key);
            pd->key = g_strdup(pd->value);
            return;
        } break;
        case P_DICT:
        {
            g_queue_pop_head(pd->stack);
        } break;
        case P_ARRAY:
        {
            g_queue_pop_head(pd->stack);
        } break;
        case P_INTEGER:
        {
            gint64 val = g_strtod(pd->value, NULL);
            gval = ghb_int_value_new(val);
        } break;
        case P_REAL:
        {
            gdouble val = g_strtod(pd->value, NULL);
            gval = ghb_double_value_new(val);
        } break;
        case P_STRING:
        {
            gval = ghb_string_value_new(pd->value);
        } break;
        case P_TRUE:
        {
            gval = ghb_bool_value_new(TRUE);
        } break;
        case P_FALSE:
        {
            gval = ghb_bool_value_new(FALSE);
        } break;
        default:
        {
            g_message("Unhandled plist type %d", id);
        } break;
    }
    if (gval)
    {
        // Get the top of the data structure stack and if it's an array
        // or dict, add the current element
        if (current == NULL)
        {
            pd->plist = gval;
            pd->closed_top = TRUE;
            return;
        }
        gtype = ghb_value_type(current);
        if (gtype == GHB_ARRAY)
        {
            ghb_array_append(current, gval);
        }
        else if (gtype == GHB_DICT)
        {
            if (pd->key == NULL)
            {
                g_warning("No key for dictionary item");
                ghb_value_free(&gval);
            }
            else
            {
                ghb_dict_set(current, pd->key, gval);
            }
        }
        else
        {
            g_error("Invalid container type. This shouldn't happen");
        }
    }
    if (g_queue_is_empty(pd->stack))
        pd->closed_top = TRUE;
}