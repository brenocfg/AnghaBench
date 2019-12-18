#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  hb_value_array_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_ARRAY ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_dup (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
hb_value_array_concat(hb_value_array_t *array, hb_value_t *value)
{
    if (hb_value_type(value) == HB_VALUE_TYPE_ARRAY)
    {
        int ii;
        int len = hb_value_array_len(value);

        for (ii = 0; ii < len; ii++)
        {
            hb_value_t * val = hb_value_array_get(value, ii);
            json_array_append_new(array, hb_value_dup(val));
        }
    }
    else
    {
        json_array_append_new(array, hb_value_dup(value));
    }
}