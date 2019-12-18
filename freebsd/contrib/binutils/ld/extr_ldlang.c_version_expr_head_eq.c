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
struct bfd_elf_version_expr {int /*<<< orphan*/  symbol; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
version_expr_head_eq (const void *p1, const void *p2)
{
  const struct bfd_elf_version_expr *e1 = p1;
  const struct bfd_elf_version_expr *e2 = p2;

  return strcmp (e1->symbol, e2->symbol) == 0;
}