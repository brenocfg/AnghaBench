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
 int /*<<< orphan*/ * json_null () ; 
 int /*<<< orphan*/ * json_string (char const*) ; 

hb_value_t * hb_value_string(const char * value)
{
    // json_string does not create a value for NULL strings.
    // So create JSON_NULL in this case
    if (value == NULL)
        return json_null();
    return json_string(value);
}