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
typedef  int hb_value_type_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
#define  HB_VALUE_TYPE_ARRAY 134 
#define  HB_VALUE_TYPE_BOOL 133 
#define  HB_VALUE_TYPE_DICT 132 
#define  HB_VALUE_TYPE_DOUBLE 131 
#define  HB_VALUE_TYPE_INT 130 
#define  HB_VALUE_TYPE_NULL 129 
#define  HB_VALUE_TYPE_STRING 128 
 int hb_value_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  json_incref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xform_array (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * xform_bool (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * xform_dict (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * xform_double (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * xform_int (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * xform_null (int) ; 
 int /*<<< orphan*/ * xform_string (int /*<<< orphan*/  const*,int) ; 

hb_value_t* hb_value_xform(const hb_value_t *value, hb_value_type_t type)
{
    hb_value_type_t src_type = hb_value_type(value);
    if (src_type == type && value != NULL)
    {
        json_incref((hb_value_t*)value);
        return (hb_value_t*)value;
    }
    switch (src_type)
    {
        default:
        case HB_VALUE_TYPE_NULL:
        {
            return xform_null(type);
        }
        case HB_VALUE_TYPE_BOOL:
        {
            return xform_bool(value, type);
        }
        case HB_VALUE_TYPE_INT:
        {
            return xform_int(value, type);
        }
        case HB_VALUE_TYPE_DOUBLE:
        {
            return xform_double(value, type);
        }
        case HB_VALUE_TYPE_STRING:
        {
            return xform_string(value, type);
        }
        case HB_VALUE_TYPE_ARRAY:
        {
            return xform_array(value, type);
        }
        case HB_VALUE_TYPE_DICT:
        {
            return xform_dict(value, type);
        }
    }
}