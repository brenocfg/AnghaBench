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
 int /*<<< orphan*/  int_timer_ctr ; 
 scalar_t__ xthal_get_ccount () ; 
 int /*<<< orphan*/  xthal_set_ccompare (int,scalar_t__) ; 

void int_timer_handler(void *arg) {
    xthal_set_ccompare(1, xthal_get_ccount()+8000000);
    int_timer_ctr++;
}