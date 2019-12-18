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
typedef  int /*<<< orphan*/  cothread_t ;

/* Variables and functions */
 int /*<<< orphan*/  co_active_handle ; 
 int /*<<< orphan*/  co_swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void co_switch(cothread_t handle)
   {
      cothread_t co_previous_handle = co_active_handle;
      co_swap(co_active_handle = handle, co_previous_handle);
   }