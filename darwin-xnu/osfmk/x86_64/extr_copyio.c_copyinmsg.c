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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  mach_msg_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  COPYIN ; 
 int copyio (int /*<<< orphan*/ ,int /*<<< orphan*/  const,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
copyinmsg(const user_addr_t user_addr, char *kernel_addr, mach_msg_size_t nbytes)
{
    return copyio(COPYIN, user_addr, kernel_addr, nbytes, NULL, 0);
}