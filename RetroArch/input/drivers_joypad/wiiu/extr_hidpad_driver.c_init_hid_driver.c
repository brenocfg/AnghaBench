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
 int /*<<< orphan*/  MAX_USERS ; 
 int hid_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_instance ; 
 int /*<<< orphan*/  hidpad_driver ; 
 int /*<<< orphan*/  wiiu_hid ; 

__attribute__((used)) static bool init_hid_driver(void)
{
   return hid_init(&hid_instance, &wiiu_hid, &hidpad_driver, MAX_USERS);
}