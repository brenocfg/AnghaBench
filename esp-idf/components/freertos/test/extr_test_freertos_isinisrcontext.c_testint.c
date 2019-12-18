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
 int /*<<< orphan*/  ets_printf (char*) ; 
 int /*<<< orphan*/  in_int_context ; 
 int /*<<< orphan*/  int_handled ; 
 scalar_t__ xPortInIsrContext () ; 
 scalar_t__ xthal_get_ccount () ; 
 int /*<<< orphan*/  xthal_set_ccompare (int,scalar_t__) ; 

__attribute__((used)) static void testint(void *arg) {
    xthal_set_ccompare(1, xthal_get_ccount()+8000000000);
    ets_printf("INT!\n");
    if (xPortInIsrContext()) in_int_context++;
    int_handled++;
}