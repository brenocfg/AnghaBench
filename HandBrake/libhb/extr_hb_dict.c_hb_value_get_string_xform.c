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
typedef  int /*<<< orphan*/  const hb_value_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_NULL ; 
 int /*<<< orphan*/  HB_VALUE_TYPE_STRING ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* hb_value_xform (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  json_string_value (int /*<<< orphan*/  const*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

char*
hb_value_get_string_xform(const hb_value_t *value)
{
    char *result;
    if (hb_value_type(value) == HB_VALUE_TYPE_NULL)
        return NULL;
    hb_value_t *v = hb_value_xform(value, HB_VALUE_TYPE_STRING);
    if (hb_value_type(v) == HB_VALUE_TYPE_NULL)
        return NULL;
    result = strdup(json_string_value(v));
    json_decref(v);
    return result;
}