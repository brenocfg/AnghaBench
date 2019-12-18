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
struct utsname {int /*<<< orphan*/  machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_U_ADDR_200 ; 
 int /*<<< orphan*/  KERNEL_U_ADDR_300 ; 
 int /*<<< orphan*/  kernel_u_addr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ uname (struct utsname*) ; 

void
_initialize_dpx2_nat (void)
{
  struct utsname uts;

  if (uname (&uts) == 0 && strcmp (uts.machine, "DPX/2200") == 0)
    kernel_u_addr = KERNEL_U_ADDR_200;
  else
    kernel_u_addr = KERNEL_U_ADDR_300;
}