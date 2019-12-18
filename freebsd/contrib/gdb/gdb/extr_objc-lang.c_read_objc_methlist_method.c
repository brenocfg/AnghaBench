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
struct objc_method {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 unsigned long read_objc_methlist_nmethods (scalar_t__) ; 
 int /*<<< orphan*/  read_objc_method (scalar_t__,struct objc_method*) ; 

__attribute__((used)) static void 
read_objc_methlist_method (CORE_ADDR addr, unsigned long num, 
			   struct objc_method *method)
{
  gdb_assert (num < read_objc_methlist_nmethods (addr));
  read_objc_method (addr + 8 + (12 * num), method);
}