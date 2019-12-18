#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t pcnt_unit_t ;
typedef  scalar_t__ int16_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {TYPE_1__* cnt_unit; } ;
struct TYPE_3__ {scalar_t__ cnt_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ PCNT ; 
 int /*<<< orphan*/  PCNT_ADDRESS_ERR_STR ; 
 int /*<<< orphan*/  PCNT_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCNT_UNIT_ERR_STR ; 
 size_t PCNT_UNIT_MAX ; 

esp_err_t pcnt_get_counter_value(pcnt_unit_t pcnt_unit, int16_t* count)
{
    PCNT_CHECK(pcnt_unit < PCNT_UNIT_MAX, PCNT_UNIT_ERR_STR, ESP_ERR_INVALID_ARG);
    PCNT_CHECK(count != NULL, PCNT_ADDRESS_ERR_STR, ESP_ERR_INVALID_ARG);
    *count = (int16_t) PCNT.cnt_unit[pcnt_unit].cnt_val;
    return ESP_OK;
}