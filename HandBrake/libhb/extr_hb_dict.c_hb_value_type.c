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
typedef  scalar_t__ hb_value_type_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_BOOL ; 
 scalar_t__ HB_VALUE_TYPE_NULL ; 
 scalar_t__ JSON_FALSE ; 
 scalar_t__ JSON_TRUE ; 
 scalar_t__ json_typeof (int /*<<< orphan*/  const*) ; 

hb_value_type_t hb_value_type(const hb_value_t *value)
{
   if (value == NULL)
        return HB_VALUE_TYPE_NULL;
    hb_value_type_t type = json_typeof(value);
    if (type == JSON_TRUE || type == JSON_FALSE)
        return HB_VALUE_TYPE_BOOL;
    return type;
}