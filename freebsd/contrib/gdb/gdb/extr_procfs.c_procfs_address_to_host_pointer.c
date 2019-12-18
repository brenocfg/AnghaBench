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
typedef  int /*<<< orphan*/  ptr ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_TO_POINTER (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 
 int /*<<< orphan*/  gdb_assert (int) ; 

__attribute__((used)) static void *
procfs_address_to_host_pointer (CORE_ADDR addr)
{
  void *ptr;

  gdb_assert (sizeof (ptr) == TYPE_LENGTH (builtin_type_void_data_ptr));
  ADDRESS_TO_POINTER (builtin_type_void_data_ptr, &ptr, addr);
  return ptr;
}