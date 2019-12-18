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
struct edge_prediction {struct edge_prediction* ep_next; TYPE_2__* ep_edge; } ;
typedef  TYPE_2__* edge ;
struct TYPE_5__ {TYPE_1__* src; } ;
struct TYPE_4__ {struct edge_prediction* predictions; } ;

/* Variables and functions */

void
remove_predictions_associated_with_edge (edge e)
{
  if (e->src->predictions)
    {
      struct edge_prediction **prediction = &e->src->predictions;
      while (*prediction)
	{
	  if ((*prediction)->ep_edge == e)
	    *prediction = (*prediction)->ep_next;
	  else
	    prediction = &((*prediction)->ep_next);
	}
    }
}