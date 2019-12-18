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
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  error_t ;

/* Variables and functions */
 int /*<<< orphan*/  ill_rpc (char*) ; 

error_t
do_mach_notify_port_deleted (mach_port_t notify, mach_port_t name)
{
  return ill_rpc ("do_mach_notify_port_deleted");
}