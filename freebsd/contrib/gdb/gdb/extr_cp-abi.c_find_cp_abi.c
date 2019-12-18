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
struct cp_abi_ops {int /*<<< orphan*/  shortname; } ;

/* Variables and functions */
 struct cp_abi_ops** cp_abis ; 
 int num_cp_abis ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct cp_abi_ops *
find_cp_abi (const char *short_name)
{
  int i;

  for (i = 0; i < num_cp_abis; i++)
    if (strcmp (cp_abis[i]->shortname, short_name) == 0)
      return cp_abis[i];

  return NULL;
}