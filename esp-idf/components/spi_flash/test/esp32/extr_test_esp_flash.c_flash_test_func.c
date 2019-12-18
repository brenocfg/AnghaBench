#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  host_id; } ;
typedef  TYPE_1__ flashtest_config_t ;
typedef  int /*<<< orphan*/  (* flash_test_func_t ) (int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  esp_flash_t ;

/* Variables and functions */
 TYPE_1__* config_list ; 
 int /*<<< orphan*/  setup_new_chip (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teardown_test_chip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flash_test_func(flash_test_func_t func, int test_num)
{
    for (int i = 0; i < test_num; i++) {
        flashtest_config_t* config = &config_list[i];
        esp_flash_t* chip;
        setup_new_chip(config, &chip);
        (*func)(chip);
        teardown_test_chip(chip, config->host_id);
    }
}