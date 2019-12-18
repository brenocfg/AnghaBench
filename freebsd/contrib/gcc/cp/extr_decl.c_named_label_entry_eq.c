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
struct named_label_entry {scalar_t__ label_decl; } ;

/* Variables and functions */

__attribute__((used)) static int
named_label_entry_eq (const void *a, const void *b)
{
  const struct named_label_entry *ent_a = (const struct named_label_entry *) a;
  const struct named_label_entry *ent_b = (const struct named_label_entry *) b;
  return ent_a->label_decl == ent_b->label_decl;
}