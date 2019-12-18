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
struct TYPE_4__ {unsigned long size; unsigned long chunk_size; unsigned long element_size; scalar_t__ pointer; void* data; } ;
typedef  TYPE_1__ stack ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 void* malloc (unsigned long) ; 

__attribute__((used)) static stack *
stack_init (unsigned long chunk_size,
	    unsigned long element_size)
{
  stack *st;

  st = malloc (sizeof (* st));
  if (!st)
    return NULL;
  st->data = malloc (chunk_size);
  if (!st->data)
    {
      free (st);
      return NULL;
    }
  st->pointer = 0;
  st->size = chunk_size;
  st->chunk_size = chunk_size;
  st->element_size = element_size;
  return st;
}