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
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_ARRAY ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int hb_value_get_int (int /*<<< orphan*/ ) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 

int hb_dict_extract_int_array(int *dst, int count,
                              const hb_dict_t * dict, const char * key)
{
    if (dict == NULL || key == NULL || dst == NULL)
    {
        return 0;
    }

    hb_value_t *val = hb_dict_get(dict, key);
    if (hb_value_type(val) != HB_VALUE_TYPE_ARRAY)
    {
        return 0;
    }

    int len = hb_value_array_len(val);
    count = count < len ? count : len;

    int ii;
    for (ii = 0; ii < count; ii++)
    {
        dst[ii] = hb_value_get_int(hb_value_array_get(val, ii));
    }
    return 1;
}