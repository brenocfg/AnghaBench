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
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
hash_varpool_node (const void *p)
{
  const struct cgraph_varpool_node *n = (const struct cgraph_varpool_node *) p;
  return (hashval_t) DECL_UID (n->decl);
}