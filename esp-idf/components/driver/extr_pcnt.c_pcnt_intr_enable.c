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
typedef  scalar_t__ pcnt_unit_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
struct TYPE_4__ {TYPE_1__ int_ena; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ PCNT ; 
 int /*<<< orphan*/  PCNT_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCNT_CNT_THR_EVENT_U0_INT_ENA_S ; 
 int /*<<< orphan*/  PCNT_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCNT_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCNT_UNIT_ERR_STR ; 
 scalar_t__ PCNT_UNIT_MAX ; 
 int /*<<< orphan*/  pcnt_spinlock ; 

esp_err_t pcnt_intr_enable(pcnt_unit_t pcnt_unit)
{
    PCNT_CHECK(pcnt_unit < PCNT_UNIT_MAX, PCNT_UNIT_ERR_STR, ESP_ERR_INVALID_ARG);
    PCNT_ENTER_CRITICAL(&pcnt_spinlock);
    PCNT.int_ena.val |= BIT(PCNT_CNT_THR_EVENT_U0_INT_ENA_S + pcnt_unit);
    PCNT_EXIT_CRITICAL(&pcnt_spinlock);
    return ESP_OK;
}