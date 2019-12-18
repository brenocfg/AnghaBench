#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct loop {int depth; TYPE_1__** pred; int /*<<< orphan*/  num_nodes; } ;
typedef  TYPE_2__* basic_block ;
struct TYPE_5__ {int loop_depth; struct loop* loop_father; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_nodes; } ;

/* Variables and functions */

void
add_bb_to_loop (basic_block bb, struct loop *loop)
{
   int i;

   bb->loop_father = loop;
   bb->loop_depth = loop->depth;
   loop->num_nodes++;
   for (i = 0; i < loop->depth; i++)
     loop->pred[i]->num_nodes++;
 }