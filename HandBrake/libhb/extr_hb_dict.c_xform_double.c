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
#define  HB_VALUE_TYPE_BOOL 132 
#define  HB_VALUE_TYPE_DOUBLE 131 
#define  HB_VALUE_TYPE_INT 130 
#define  HB_VALUE_TYPE_NULL 129 
#define  HB_VALUE_TYPE_STRING 128 
 int /*<<< orphan*/  free (char*) ; 
 char* hb_strdup_printf (char*,double) ; 
 int /*<<< orphan*/ * json_boolean (int) ; 
 int /*<<< orphan*/ * json_integer (double) ; 
 int /*<<< orphan*/ * json_null () ; 
 int /*<<< orphan*/ * json_real (double) ; 
 double json_real_value (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * json_string (char*) ; 

__attribute__((used)) static hb_value_t* xform_double(const hb_value_t *value, hb_value_type_t type)
{
    double d = json_real_value(value);
    switch (type)
    {
        default:
        case HB_VALUE_TYPE_NULL:
            return json_null();
        case HB_VALUE_TYPE_BOOL:
            return json_boolean((int)d != 0);
        case HB_VALUE_TYPE_INT:
            return json_integer(d);
        case HB_VALUE_TYPE_DOUBLE:
            return json_real(d);
        case HB_VALUE_TYPE_STRING:
        {
            char *s = hb_strdup_printf("%g", d);
            hb_value_t *v = json_string(s);
            free(s);
            return v;
        }
    }
}