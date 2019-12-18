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
typedef  int /*<<< orphan*/  HIDClient ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/ * alloc_zeroed (int,int) ; 

__attribute__((used)) static HIDClient *new_hidclient(void)
{
   RARCH_LOG("[hid]: new_hidclient()\n");
   return alloc_zeroed(32, sizeof(HIDClient));
}