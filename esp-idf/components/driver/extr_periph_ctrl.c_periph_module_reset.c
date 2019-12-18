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
typedef  int /*<<< orphan*/  periph_module_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPORT_CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPORT_SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rst_en_mask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_rst_en_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  periph_spinlock ; 
 int /*<<< orphan*/  portENTER_CRITICAL_SAFE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL_SAFE (int /*<<< orphan*/ *) ; 

void periph_module_reset(periph_module_t periph)
{
    portENTER_CRITICAL_SAFE(&periph_spinlock);
    DPORT_SET_PERI_REG_MASK(get_rst_en_reg(periph), get_rst_en_mask(periph, false));
    DPORT_CLEAR_PERI_REG_MASK(get_rst_en_reg(periph), get_rst_en_mask(periph, false));
    portEXIT_CRITICAL_SAFE(&periph_spinlock);
}