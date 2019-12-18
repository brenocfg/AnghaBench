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

/* Variables and functions */
 int /*<<< orphan*/  HB_VALUE_TYPE_BOOL ; 
 int /*<<< orphan*/ * hb_value_xform (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int json_is_true (int /*<<< orphan*/ *) ; 

int hb_value_get_bool(const hb_value_t *value)
{
    int result;
    hb_value_t *v = hb_value_xform(value, HB_VALUE_TYPE_BOOL);
    result = json_is_true(v);
    json_decref(v);
    return result;
}