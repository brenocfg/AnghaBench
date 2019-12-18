#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct partition_pair_d {int dummy; } ;
typedef  TYPE_1__* partition_pair_p ;
typedef  TYPE_2__* coalesce_list_p ;
struct TYPE_6__ {TYPE_1__** list; } ;
struct TYPE_5__ {int second_partition; int first_partition; struct TYPE_5__* next; scalar_t__ cost; } ;

/* Variables and functions */
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static partition_pair_p
find_partition_pair (coalesce_list_p cl, int p1, int p2, bool create)
{
  partition_pair_p node, tmp;
  int s;
    
  /* Normalize so that p1 is the smaller value.  */
  if (p2 < p1)
    {
      s = p1;
      p1 = p2;
      p2 = s;
    }
  
  tmp = NULL;

  /* The list is sorted such that if we find a value greater than p2,
     p2 is not in the list.  */
  for (node = cl->list[p1]; node; node = node->next)
    {
      if (node->second_partition == p2)
        return node;
      else
        if (node->second_partition > p2)
	  break;
     tmp = node;
    }

  if (!create)
    return NULL;

  node = (partition_pair_p) xmalloc (sizeof (struct partition_pair_d));
  node->first_partition = p1;
  node->second_partition = p2;
  node->cost = 0;
    
  if (tmp != NULL)
    {
      node->next = tmp->next;
      tmp->next = node;
    }
  else
    {
      /* This is now the first node in the list.  */
      node->next = cl->list[p1];
      cl->list[p1] = node;
    }

  return node;
}