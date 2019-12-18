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
struct elf_symbol {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
elf_sym_name_compare (const void *arg1, const void *arg2)
{
  const struct elf_symbol *s1 = (const struct elf_symbol *) arg1;
  const struct elf_symbol *s2 = (const struct elf_symbol *) arg2;
  return strcmp (s1->name, s2->name);
}