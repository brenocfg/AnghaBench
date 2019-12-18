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
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/ * alloc_zeroed (int,int) ; 

__attribute__((used)) static wiiu_hid_t *new_hid(void)
{
   RARCH_LOG("[hid]: new_hid()\n");
   return alloc_zeroed(4, sizeof(wiiu_hid_t));
}