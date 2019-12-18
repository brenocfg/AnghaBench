#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct et_node {TYPE_3__* data; TYPE_2__* father; } ;
typedef  enum cdi_direction { ____Placeholder_cdi_direction } cdi_direction ;
typedef  TYPE_3__* basic_block ;
struct TYPE_8__ {TYPE_1__** dom; } ;
struct TYPE_7__ {struct et_node* son; } ;
struct TYPE_6__ {struct et_node* right; } ;

/* Variables and functions */

basic_block
next_dom_son (enum cdi_direction dir, basic_block bb)
{
  struct et_node *next = bb->dom[dir]->right;

  return next->father->son == next ? NULL : next->data;
}