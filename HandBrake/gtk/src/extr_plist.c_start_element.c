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
struct TYPE_3__ {int /*<<< orphan*/ * key; int /*<<< orphan*/ * plist; int /*<<< orphan*/  stack; int /*<<< orphan*/  tag_stack; scalar_t__ closed_top; } ;
typedef  TYPE_1__ parse_data_t ;
typedef  int /*<<< orphan*/ * gpointer ;
typedef  size_t gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {size_t id; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  scalar_t__ GhbType ;
typedef  int /*<<< orphan*/  GMarkupParseContext ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 scalar_t__ GHB_ARRAY ; 
 scalar_t__ GHB_DICT ; 
#define  P_ARRAY 138 
#define  P_DATA 137 
#define  P_DATE 136 
#define  P_DICT 135 
#define  P_FALSE 134 
#define  P_INTEGER 133 
#define  P_KEY 132 
#define  P_PLIST 131 
#define  P_REAL 130 
#define  P_STRING 129 
#define  P_TRUE 128 
 size_t TAG_MAP_SZ ; 
 int /*<<< orphan*/  g_error (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_queue_peek_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_queue_push_head (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_warning (char*,...) ; 
 int /*<<< orphan*/  ghb_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_new () ; 
 int /*<<< orphan*/ * ghb_dict_new () ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 scalar_t__ ghb_value_type (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* tag_map ; 

__attribute__((used)) static void
start_element(
    GMarkupParseContext *ctx,
    const gchar *name,
    const gchar **attr_names,
    const gchar **attr_values,
    gpointer ud,
    GError **error)
{
    parse_data_t *pd = (parse_data_t*)ud;
    union
    {
        gint id;
        gpointer pid;
    } id;
    gint ii;

    // Check to see if the first element found has been closed
    // If so, ignore any junk following it.
    if (pd->closed_top)
        return;

    for (ii = 0; ii < TAG_MAP_SZ; ii++)
    {
        if (strcmp(name, tag_map[ii].tag) == 0)
        {
            id.id = tag_map[ii].id;
            break;
        }
    }
    if (ii == TAG_MAP_SZ)
    {
        g_warning("Unrecognized start tag (%s)", name);
        return;
    }
    g_queue_push_head(pd->tag_stack, id.pid);
    GhbType gtype = 0;
    GhbValue *gval = NULL;
    GhbValue *current = g_queue_peek_head(pd->stack);
    switch (id.id)
    {
        case P_PLIST:
        { // Ignore
        } break;
        case P_KEY:
        {
            if (pd->key) g_free(pd->key);
            pd->key = NULL;
        } break;
        case P_DICT:
        {
            gval = ghb_dict_new();
            g_queue_push_head(pd->stack, gval);
        } break;
        case P_ARRAY:
        {
            gval = ghb_array_new();
            g_queue_push_head(pd->stack, gval);
        } break;
        case P_INTEGER:
        {
        } break;
        case P_REAL:
        {
        } break;
        case P_STRING:
        {
        } break;
        case P_DATE:
        {
        } break;
        case P_TRUE:
        {
        } break;
        case P_FALSE:
        {
        } break;
        case P_DATA:
        {
        } break;
    }
    // Add the element to the current container
    if (gval)
    { // There's an element to add
        if (current == NULL)
        {
            pd->plist = gval;
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
}