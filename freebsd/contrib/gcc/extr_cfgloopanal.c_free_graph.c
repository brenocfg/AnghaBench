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
struct graph {int n_vertices; struct graph* vertices; struct graph* succ_next; struct graph* succ; } ;
struct edge {int n_vertices; struct edge* vertices; struct edge* succ_next; struct edge* succ; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct graph*) ; 

__attribute__((used)) static void
free_graph (struct graph *g)
{
  struct edge *e, *n;
  int i;

  for (i = 0; i < g->n_vertices; i++)
    for (e = g->vertices[i].succ; e; e = n)
      {
	n = e->succ_next;
	free (e);
      }
  free (g->vertices);
  free (g);
}