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
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  user_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  COPYINSTR ; 
 int copyio (int /*<<< orphan*/ ,int /*<<< orphan*/  const,char*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

int
copyinstr(const user_addr_t user_addr,  char *kernel_addr, vm_size_t nbytes, vm_size_t *lencopied)
{
    *lencopied = 0;

    return copyio(COPYINSTR, user_addr, kernel_addr, nbytes, lencopied, 0);
}