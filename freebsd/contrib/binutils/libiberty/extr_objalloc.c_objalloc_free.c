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
struct objalloc_chunk {struct objalloc_chunk* next; scalar_t__ chunks; } ;
struct objalloc {struct objalloc* next; scalar_t__ chunks; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct objalloc_chunk*) ; 

void
objalloc_free (struct objalloc *o)
{
  struct objalloc_chunk *l;

  l = (struct objalloc_chunk *) o->chunks;
  while (l != NULL)
    {
      struct objalloc_chunk *next;

      next = l->next;
      free (l);
      l = next;
    }

  free (o);
}