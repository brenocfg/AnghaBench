#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t i2s_port_t ;
typedef  int /*<<< orphan*/  i2s_isr_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  esp_intr_alloc (int /*<<< orphan*/ ,int,void (*) (void*),void*,int /*<<< orphan*/ *) ; 
 TYPE_1__* i2s_periph_signal ; 

__attribute__((used)) static esp_err_t i2s_isr_register(i2s_port_t i2s_num, int intr_alloc_flags, void (*fn)(void*), void * arg, i2s_isr_handle_t *handle)
{
    return esp_intr_alloc(i2s_periph_signal[i2s_num].irq, intr_alloc_flags, fn, arg, handle);
}