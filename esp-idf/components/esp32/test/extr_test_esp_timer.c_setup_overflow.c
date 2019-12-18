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

/* Variables and functions */
 int /*<<< orphan*/  esp_timer_impl_get_overflow_val () ; 
 int /*<<< orphan*/  esp_timer_impl_set_overflow_val (int) ; 
 int /*<<< orphan*/  s_old_overflow_val ; 

__attribute__((used)) static void setup_overflow(void)
{
    s_old_overflow_val = esp_timer_impl_get_overflow_val();
    /* Overflow every 0.1 sec.
     * Chosen so that it is 0 modulo s_timer_ticks_per_us (which is 80),
     * to prevent roundoff error on each overflow.
     */
    esp_timer_impl_set_overflow_val(8000000);
}