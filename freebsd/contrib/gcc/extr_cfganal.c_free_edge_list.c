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
struct edge_list {struct edge_list* index_to_edge; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct edge_list*) ; 

void
free_edge_list (struct edge_list *elist)
{
  if (elist)
    {
      free (elist->index_to_edge);
      free (elist);
    }
}