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
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_array_init () ; 

__attribute__((used)) static hb_value_t * value_pair(hb_value_t * v1, hb_value_t * v2)
{
    hb_value_t *array = hb_value_array_init();
    hb_value_array_append(array, v1);
    hb_value_array_append(array, v2);
    return array;
}