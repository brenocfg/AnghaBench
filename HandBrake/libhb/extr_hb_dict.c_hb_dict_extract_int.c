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
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/  const*,char const*) ; 
 int hb_value_get_int (int /*<<< orphan*/ *) ; 

int hb_dict_extract_int(int *dst, const hb_dict_t * dict, const char * key)
{
    if (dict == NULL || key == NULL || dst == NULL)
    {
        return 0;
    }

    hb_value_t *val = hb_dict_get(dict, key);
    if (val == NULL)
    {
        return 0;
    }

    *dst = hb_value_get_int(val);
    return 1;
}