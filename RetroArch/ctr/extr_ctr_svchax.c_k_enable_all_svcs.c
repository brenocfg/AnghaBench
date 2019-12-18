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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ CURRENT_KPROCESS ; 
 scalar_t__ CURRENT_KTHREAD ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 

__attribute__((used)) static void k_enable_all_svcs(u32 isNew3DS)
{
   u32* thread_ACL = *(*(u32***)CURRENT_KTHREAD + 0x22) - 0x6;
   u32* process_ACL = *(u32**)CURRENT_KPROCESS + (isNew3DS ? 0x24 : 0x22);

   memset(thread_ACL, 0xFF, 0x10);
   memset(process_ACL, 0xFF, 0x10);
}