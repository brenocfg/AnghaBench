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
typedef  int /*<<< orphan*/  hb_value_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_error (char*,int,int) ; 
 int /*<<< orphan*/  json_array_set_new (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int json_array_size (int /*<<< orphan*/ *) ; 

void
hb_value_array_set(hb_value_array_t *array, int index, hb_value_t *value)
{
    if (index < 0 || index >= json_array_size(array))
    {
        hb_error("hb_value_array_set: invalid index %d size %zu",
                 index, json_array_size(array));
        return;
    }
    json_array_set_new(array, index, value);
}