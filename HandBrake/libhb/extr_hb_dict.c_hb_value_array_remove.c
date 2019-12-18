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
typedef  int /*<<< orphan*/  hb_value_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_array_remove (int /*<<< orphan*/ *,int) ; 

void
hb_value_array_remove(hb_value_array_t *array, int index)
{
    json_array_remove(array, index);
}