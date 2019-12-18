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
 int current_function_calls_alloca ; 
 int current_function_calls_setjmp ; 

void
clear_special_calls (void)
{
  current_function_calls_alloca = false;
  current_function_calls_setjmp = false;
}