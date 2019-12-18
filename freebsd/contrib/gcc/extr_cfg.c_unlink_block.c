#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* basic_block ;
struct TYPE_7__ {TYPE_2__* next_bb; TYPE_1__* prev_bb; } ;
struct TYPE_6__ {TYPE_1__* prev_bb; } ;
struct TYPE_5__ {TYPE_2__* next_bb; } ;

/* Variables and functions */

void
unlink_block (basic_block b)
{
  b->next_bb->prev_bb = b->prev_bb;
  b->prev_bb->next_bb = b->next_bb;
  b->prev_bb = NULL;
  b->next_bb = NULL;
}