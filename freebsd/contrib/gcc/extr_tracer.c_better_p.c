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
typedef  TYPE_3__* edge ;
struct TYPE_8__ {scalar_t__ count; int probability; TYPE_2__* dest; TYPE_1__* src; } ;
struct TYPE_7__ {scalar_t__ index; } ;
struct TYPE_6__ {int frequency; scalar_t__ index; } ;

/* Variables and functions */

__attribute__((used)) static bool
better_p (edge e1, edge e2)
{
  if (e1->count != e2->count)
    return e1->count > e2->count;
  if (e1->src->frequency * e1->probability !=
      e2->src->frequency * e2->probability)
    return (e1->src->frequency * e1->probability
	    > e2->src->frequency * e2->probability);
  /* This is needed to avoid changes in the decision after
     CFG is modified.  */
  if (e1->src != e2->src)
    return e1->src->index > e2->src->index;
  return e1->dest->index > e2->dest->index;
}