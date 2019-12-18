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
 int /*<<< orphan*/ * json_false () ; 
 int /*<<< orphan*/ * json_integer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_null () ; 
 int /*<<< orphan*/ * json_real (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_string (char const*) ; 
 char* json_string_value (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * json_true () ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strtod (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strtoll (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hb_value_t* xform_string(const hb_value_t *value, hb_value_type_t type)
{
    const char *s = json_string_value(value);
    switch (type)
    {
        default:
        case HB_VALUE_TYPE_NULL:
        {
            return json_null();
        }
        case HB_VALUE_TYPE_BOOL:
        {
            if (!strcasecmp(s, "true") ||
                !strcasecmp(s, "yes")  ||
                !strcasecmp(s, "1"))
            {
                return json_true();
            }
            return json_false();
        }
        case HB_VALUE_TYPE_INT:
        {
            return json_integer(strtoll(s, NULL, 0));
        }
        case HB_VALUE_TYPE_DOUBLE:
        {
            return json_real(strtod(s, NULL));
        }
        case HB_VALUE_TYPE_STRING:
        {
            return json_string(s);
        }
    }
}