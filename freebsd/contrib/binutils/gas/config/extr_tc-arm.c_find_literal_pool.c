#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ section; scalar_t__ sub_section; struct TYPE_4__* next; } ;
typedef  TYPE_1__ literal_pool ;

/* Variables and functions */
 TYPE_1__* list_of_pools ; 
 scalar_t__ now_seg ; 
 scalar_t__ now_subseg ; 

__attribute__((used)) static literal_pool *
find_literal_pool (void)
{
  literal_pool * pool;

  for (pool = list_of_pools; pool != NULL; pool = pool->next)
    {
      if (pool->section == now_seg
	  && pool->sub_section == now_subseg)
	break;
    }

  return pool;
}