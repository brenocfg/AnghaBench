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
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  htab_hash_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
version_expr_head_hash (const void *p)
{
  const struct bfd_elf_version_expr *e = p;

  return htab_hash_string (e->symbol);
}