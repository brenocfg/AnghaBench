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
typedef  int /*<<< orphan*/  wiiu_hid_t ;

/* Variables and functions */
 int /*<<< orphan*/  synchronized_process_adapters (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wiiu_hid_poll(void *data)
{
   wiiu_hid_t *hid = (wiiu_hid_t *)data;
   if (!hid)
      return;

   synchronized_process_adapters(hid);
}