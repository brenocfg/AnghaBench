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
struct cgraph_edge {int /*<<< orphan*/  call_stmt; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  htab_hash_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
edge_hash (const void *x)
{
  return htab_hash_pointer (((struct cgraph_edge *) x)->call_stmt);
}