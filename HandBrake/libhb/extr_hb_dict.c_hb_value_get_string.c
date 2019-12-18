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
 scalar_t__ HB_VALUE_TYPE_STRING ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/  const*) ; 
 char const* json_string_value (int /*<<< orphan*/  const*) ; 

const char * hb_value_get_string(const hb_value_t *value)
{
    if (hb_value_type(value) != HB_VALUE_TYPE_STRING) return NULL;
    return json_string_value(value);
}