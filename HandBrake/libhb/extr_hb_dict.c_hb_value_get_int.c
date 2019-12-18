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
typedef  int /*<<< orphan*/  json_int_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_VALUE_TYPE_INT ; 
 int /*<<< orphan*/ * hb_value_xform (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_integer_value (int /*<<< orphan*/ *) ; 

json_int_t hb_value_get_int(const hb_value_t *value)
{
    json_int_t result;
    hb_value_t *v = hb_value_xform(value, HB_VALUE_TYPE_INT);
    result = json_integer_value(v);
    json_decref(v);
    return result;
}