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
struct cgraph_varpool_node {int /*<<< orphan*/  decl; } ;

/* Variables and functions */
 scalar_t__ DECL_UID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
eq_varpool_node (const void *p1, const void *p2)
{
  const struct cgraph_varpool_node *n1 =
    (const struct cgraph_varpool_node *) p1;
  const struct cgraph_varpool_node *n2 =
    (const struct cgraph_varpool_node *) p2;
  return DECL_UID (n1->decl) == DECL_UID (n2->decl);
}