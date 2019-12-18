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
struct cp_abi_ops {int dummy; } ;

/* Variables and functions */
 struct cp_abi_ops current_cp_abi ; 
 struct cp_abi_ops* find_cp_abi (char const*) ; 

__attribute__((used)) static int
switch_to_cp_abi (const char *short_name)
{
  struct cp_abi_ops *abi;

  abi = find_cp_abi (short_name);
  if (abi == NULL)
    return 0;

  current_cp_abi = *abi;
  return 1;
}