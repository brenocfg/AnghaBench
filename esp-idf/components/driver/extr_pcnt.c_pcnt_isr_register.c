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
typedef  int /*<<< orphan*/  pcnt_isr_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ETS_PCNT_INTR_SOURCE ; 
 int /*<<< orphan*/  PCNT_ADDRESS_ERR_STR ; 
 int /*<<< orphan*/  PCNT_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_intr_alloc (int /*<<< orphan*/ ,int,void (*) (void*),void*,int /*<<< orphan*/ *) ; 

esp_err_t pcnt_isr_register(void (*fun)(void*), void * arg, int intr_alloc_flags, pcnt_isr_handle_t *handle)
{
    PCNT_CHECK(fun != NULL, PCNT_ADDRESS_ERR_STR, ESP_ERR_INVALID_ARG);
    return esp_intr_alloc(ETS_PCNT_INTR_SOURCE, intr_alloc_flags, fun, arg, handle);
}