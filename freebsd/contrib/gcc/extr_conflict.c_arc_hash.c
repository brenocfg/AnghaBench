#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hashval_t ;
typedef  TYPE_1__* const_conflict_graph_arc ;
struct TYPE_2__ {int /*<<< orphan*/  larger; int /*<<< orphan*/  smaller; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFLICT_HASH_FN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
arc_hash (const void *arcp)
{
  const_conflict_graph_arc arc = (const_conflict_graph_arc) arcp;

  return CONFLICT_HASH_FN (arc->smaller, arc->larger);
}