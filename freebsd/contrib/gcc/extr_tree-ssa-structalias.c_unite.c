#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int size; unsigned int* rep; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* graph ; 

__attribute__((used)) static bool
unite (unsigned int to, unsigned int from)
{
  gcc_assert (to < graph->size && from < graph->size);
  if (to != from && graph->rep[from] != to)
    {
      graph->rep[from] = to;
      return true;
    }
  return false;
}