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
struct constant_descriptor_tree {scalar_t__ hash; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int compare_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
const_desc_eq (const void *p1, const void *p2)
{
  const struct constant_descriptor_tree *c1 = p1;
  const struct constant_descriptor_tree *c2 = p2;
  if (c1->hash != c2->hash)
    return 0;
  return compare_constant (c1->value, c2->value);
}