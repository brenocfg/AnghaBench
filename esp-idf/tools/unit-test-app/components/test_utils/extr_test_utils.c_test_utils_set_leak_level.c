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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  size_t esp_comp_leak_t ;

/* Variables and functions */
 size_t COMP_LEAK_ALL ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 size_t TYPE_LEAK_MAX ; 
 size_t** test_unity_leak_level ; 

esp_err_t test_utils_set_leak_level(size_t leak_level, esp_type_leak_t type_of_leak, esp_comp_leak_t component)
{
    if (type_of_leak >= TYPE_LEAK_MAX || component >= COMP_LEAK_ALL) {
        return ESP_ERR_INVALID_ARG;
    }
    test_unity_leak_level[type_of_leak][component] = leak_level;
    return ESP_OK;
}