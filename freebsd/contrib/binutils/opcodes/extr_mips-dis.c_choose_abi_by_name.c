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
struct mips_abi_choice {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct mips_abi_choice*) ; 
 struct mips_abi_choice* mips_abi_choices ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,unsigned int) ; 

__attribute__((used)) static const struct mips_abi_choice *
choose_abi_by_name (const char *name, unsigned int namelen)
{
  const struct mips_abi_choice *c;
  unsigned int i;

  for (i = 0, c = NULL; i < ARRAY_SIZE (mips_abi_choices) && c == NULL; i++)
    if (strncmp (mips_abi_choices[i].name, name, namelen) == 0
	&& strlen (mips_abi_choices[i].name) == namelen)
      c = &mips_abi_choices[i];

  return c;
}