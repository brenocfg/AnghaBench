#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pointer; scalar_t__ element_size; char* data; } ;
typedef  TYPE_1__ stack ;

/* Variables and functions */

__attribute__((used)) static char *
stack_pop (stack *st)
{
  if (st->pointer < st->element_size)
    {
      st->pointer = 0;
      return NULL;
    }
  st->pointer -= st->element_size;
  return st->data + st->pointer;
}