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
 int /*<<< orphan*/  DeleteSema (scalar_t__) ; 
 int /*<<< orphan*/  _lock () ; 
 scalar_t__ _lock_sema_id ; 
 int /*<<< orphan*/  _unlock () ; 

void _free_ps2_io(void) {
   _lock();
   _unlock();
   if(_lock_sema_id >= 0) DeleteSema(_lock_sema_id);
}