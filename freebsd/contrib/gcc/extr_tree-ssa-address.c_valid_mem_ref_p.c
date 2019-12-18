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
struct mem_address {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  addr_for_mem_ref (struct mem_address*,int) ; 
 int memory_address_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
valid_mem_ref_p (enum machine_mode mode, struct mem_address *addr)
{
  rtx address;

  address = addr_for_mem_ref (addr, false);
  if (!address)
    return false;

  return memory_address_p (mode, address);
}