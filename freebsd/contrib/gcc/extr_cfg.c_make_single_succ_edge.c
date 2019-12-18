#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_10__ {int /*<<< orphan*/  count; } ;
struct TYPE_9__ {int /*<<< orphan*/  count; int /*<<< orphan*/  probability; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_BR_PROB_BASE ; 
 TYPE_1__* make_edge (TYPE_2__*,TYPE_2__*,int) ; 

edge
make_single_succ_edge (basic_block src, basic_block dest, int flags)
{
  edge e = make_edge (src, dest, flags);

  e->probability = REG_BR_PROB_BASE;
  e->count = src->count;
  return e;
}