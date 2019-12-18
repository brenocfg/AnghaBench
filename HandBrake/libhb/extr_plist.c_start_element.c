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
struct TYPE_3__ {void* plist; int /*<<< orphan*/ * key; int /*<<< orphan*/  stack; int /*<<< orphan*/  tag_stack; int /*<<< orphan*/ * value; scalar_t__ closed_top; } ;
typedef  TYPE_1__ parse_data_t ;
typedef  scalar_t__ hb_value_type_t ;
typedef  void hb_value_t ;
struct TYPE_4__ {int id; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_ARRAY ; 
 scalar_t__ HB_VALUE_TYPE_DICT ; 
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
 int TAG_MAP_SZ ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (void*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  hb_error (char*,...) ; 
 int /*<<< orphan*/  hb_value_array_append (void*,void*) ; 
 void* hb_value_array_init () ; 
 int /*<<< orphan*/  hb_value_free (void**) ; 
 scalar_t__ hb_value_type (void*) ; 
 void* queue_peek_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_push_head (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* tag_map ; 

__attribute__((used)) static void
start_element(
    void *ud,
    const xmlChar *xname,
    const xmlChar **attr_names)
{
    char *name = (char*)xname;
    parse_data_t *pd = (parse_data_t*)ud;
    union
    {
        int id;
        void * pid;
    } id;
    int ii;

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
        hb_error("Unrecognized start tag (%s)", name);
        return;
    }
    if (pd->value)
    {
        free(pd->value);
        pd->value = NULL;
    }
    queue_push_head(pd->tag_stack, id.pid);
    hb_value_type_t gtype = 0;
    hb_value_t *gval = NULL;
    hb_value_t *current = queue_peek_head(pd->stack);
    switch (id.id)
    {
        case P_PLIST:
        { // Ignore
        } break;
        case P_KEY:
        {
            if (pd->key) free(pd->key);
            pd->key = NULL;
        } break;
        case P_DICT:
        {
            gval = hb_dict_init();
            queue_push_head(pd->stack, gval);
        } break;
        case P_ARRAY:
        {
            gval = hb_value_array_init();
            queue_push_head(pd->stack, gval);
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
}