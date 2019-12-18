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
typedef  size_t esp_type_leak_t ;
typedef  int esp_comp_leak_t ;

/* Variables and functions */
 int COMP_LEAK_ALL ; 
 size_t TYPE_LEAK_MAX ; 
 size_t** test_unity_leak_level ; 

size_t test_utils_get_leak_level(esp_type_leak_t type_of_leak, esp_comp_leak_t component)
{
    size_t leak_level = 0;
    if (type_of_leak >= TYPE_LEAK_MAX || component > COMP_LEAK_ALL) {
        leak_level = 0;
    } else {
        if (component == COMP_LEAK_ALL) {
            for (int comp = 0; comp < COMP_LEAK_ALL; ++comp) {
                leak_level += test_unity_leak_level[type_of_leak][comp];
            }
        } else {
            leak_level = test_unity_leak_level[type_of_leak][component];
        }
    }
    return leak_level;
}