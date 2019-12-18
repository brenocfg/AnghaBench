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
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  hb_value_array_t ;
struct TYPE_3__ {scalar_t__ enforce_order; } ;
typedef  TYPE_1__ hb_filter_object_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int hb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_error (char*,int) ; 
 TYPE_1__* hb_filter_get (int) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_value_array_insert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 

void hb_add_filter2( hb_value_array_t * list, hb_dict_t * filter_dict )
{
    int new_id = hb_dict_get_int(filter_dict, "ID");

    hb_filter_object_t * filter = hb_filter_get(new_id);
    if (filter == NULL)
    {
        hb_error("hb_add_filter2: Invalid filter ID %d", new_id);
        hb_value_free(&filter_dict);
        return;
    }
    if (filter->enforce_order)
    {
        // Find the position in the filter chain this filter belongs in
        int ii, len;

        len = hb_value_array_len(list);
        for( ii = 0; ii < len; ii++ )
        {
            hb_value_t * f = hb_value_array_get(list, ii);
            int id = hb_dict_get_int(f, "ID");
            if (id > new_id)
            {
                hb_value_array_insert(list, ii, filter_dict);
                return;
            }
            else if ( id == new_id )
            {
                // Don't allow the same filter to be added twice
                hb_value_free(&filter_dict);
                return;
            }
        }
    }
    // No position found or order not enforced for this filter
    hb_value_array_append(list, filter_dict);
}