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
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int closed_top; char* value; int /*<<< orphan*/  stack; int /*<<< orphan*/ * key; int /*<<< orphan*/ * plist; int /*<<< orphan*/  tag_stack; } ;
typedef  TYPE_1__ parse_data_t ;
typedef  scalar_t__ hb_value_type_t ;
typedef  int /*<<< orphan*/  hb_value_t ;
struct TYPE_4__ {int id; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_ARRAY ; 
 scalar_t__ HB_VALUE_TYPE_DICT ; 
#define  P_ARRAY 136 
#define  P_DICT 135 
#define  P_FALSE 134 
#define  P_INTEGER 133 
#define  P_KEY 132 
#define  P_PLIST 131 
#define  P_REAL 130 
#define  P_STRING 129 
#define  P_TRUE 128 
 int TAG_MAP_SZ ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_error (char*,...) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_bool (int) ; 
 int /*<<< orphan*/ * hb_value_double (double) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_value_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_value_string (char const*) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * queue_peek_head (int /*<<< orphan*/ ) ; 
 void* queue_pop_head (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 double strtod (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strtoll (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* tag_map ; 

__attribute__((used)) static void
end_element(
    void *ud,
    const xmlChar *xname)
{
    char *name = (char*)xname;
    parse_data_t *pd = (parse_data_t*)ud;
    int id;
    union
    {
        int id;
        void * pid;
    } start_id;
    int ii;

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
        hb_error("Unrecognized start tag (%s)", name);
        return;
    }
    start_id.pid = queue_pop_head(pd->tag_stack);
    if (start_id.id != id)
        hb_error("start tag != end tag: (%s %d) %d", name, id, id);

    hb_value_t *gval = NULL;
    hb_value_t *current = queue_peek_head(pd->stack);
    hb_value_type_t gtype = 0;
    const char *value;
    if (pd->value != NULL)
        value = pd->value;
    else
        value = "";
    switch (id)
    {
        case P_PLIST:
        { // Ignore
        } break;
        case P_KEY:
        {
            if (pd->key) free(pd->key);
            pd->key = strdup(value);
            return;
        } break;
        case P_DICT:
        {
            queue_pop_head(pd->stack);
        } break;
        case P_ARRAY:
        {
            queue_pop_head(pd->stack);
        } break;
        case P_INTEGER:
        {
            uint64_t val = strtoll(value, NULL, 0);
            gval = hb_value_int(val);
        } break;
        case P_REAL:
        {
            double val = strtod(value, NULL);
            gval = hb_value_double(val);
        } break;
        case P_STRING:
        {
            gval = hb_value_string(value);
        } break;
        case P_TRUE:
        {
            gval = hb_value_bool(1);
        } break;
        case P_FALSE:
        {
            gval = hb_value_bool(0);
        } break;
        default:
        {
            hb_error("Unhandled plist type %d", id);
        } break;
    }
    if (gval)
    {
        // Get the top of the data structure stack and if it's an array
        // or dict, add the current element
        if (current == NULL)
        {
            pd->plist = gval;
            pd->closed_top = 1;
            return;
        }
        gtype = hb_value_type(current);
        if (gtype == HB_VALUE_TYPE_ARRAY)
        {
            hb_value_array_append(current, gval);
        }
        else if (gtype == HB_VALUE_TYPE_DICT)
        {
            if (pd->key == NULL)
            {
                hb_error("No key for dictionary item");
                hb_value_free(&gval);
            }
            else
            {
                hb_dict_set(current, pd->key, gval);
            }
        }
        else
        {
            hb_error("Invalid container type. This shouldn't happen");
        }
    }
    if (queue_is_empty(pd->stack))
        pd->closed_top = 1;
}