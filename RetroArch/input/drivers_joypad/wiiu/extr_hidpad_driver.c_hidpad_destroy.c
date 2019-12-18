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
 int /*<<< orphan*/  hid_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_instance ; 
 int hidpad_ready ; 

__attribute__((used)) static void hidpad_destroy(void)
{
   hidpad_ready = false;

   hid_deinit(&hid_instance);
}