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
typedef  int /*<<< orphan*/  const hb_value_t ;
struct TYPE_3__ {int num; int den; } ;
typedef  TYPE_1__ hb_rational_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_DICT ; 
 scalar_t__ HB_VALUE_TYPE_STRING ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  hb_str_vfree (char**) ; 
 char** hb_str_vsplit (char const*,char) ; 
 void* hb_value_get_int (int /*<<< orphan*/  const*) ; 
 char* hb_value_get_string (int /*<<< orphan*/  const*) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ isdigit (char) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 

int hb_dict_extract_rational(hb_rational_t *dst, const hb_dict_t * dict,
                                                 const char * key)
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

    if (hb_value_type(val) == HB_VALUE_TYPE_DICT)
    {
        hb_value_t * num_val = hb_dict_get(val, "Num");
        if (num_val == NULL)
        {
            return 0;
        }
        hb_value_t * den_val = hb_dict_get(val, "Den");
        if (den_val == NULL)
        {
            return 0;
        }

        dst->num = hb_value_get_int(num_val);
        dst->den = hb_value_get_int(den_val);
        return 1;
    }
    else if (hb_value_type(val) == HB_VALUE_TYPE_STRING)
    {
        const char * str = hb_value_get_string(val);
        char ** rational = hb_str_vsplit(str, '/');
        if (rational[0] != NULL && rational[1] != NULL &&
            isdigit(rational[0][0]) && isdigit(rational[1][0]))
        {
            char *num_end, *den_end;

            // found rational format value
            int num = strtol(rational[0], &num_end, 0);
            int den = strtol(rational[1], &den_end, 0);
            // confirm that the 2 components were entirely numbers
            if (num_end[0] == 0 && den_end[0] == 0)
            {
                dst->num = num;
                dst->den = den;
                hb_str_vfree(rational);
                return 1;
            }
        }
        hb_str_vfree(rational);
    }

    return 0;
}