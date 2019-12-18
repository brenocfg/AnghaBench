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
struct object_block {int /*<<< orphan*/  const* sect; } ;
typedef  int /*<<< orphan*/  section ;

/* Variables and functions */

__attribute__((used)) static int
object_block_entry_eq (const void *p1, const void *p2)
{
  const struct object_block *old = p1;
  const section *new = p2;

  return old->sect == new;
}