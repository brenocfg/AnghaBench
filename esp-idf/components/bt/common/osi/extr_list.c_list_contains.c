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
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  list_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/  const*) ; 
 void const* list_node (int /*<<< orphan*/  const*) ; 

bool list_contains(const list_t *list, const void *data)
{
  assert(list != NULL);
  assert(data != NULL);

  for (const list_node_t *node = list_begin(list); node != list_end(list); node = list_next(node)) {
    if (list_node(node) == data) {
      return true;
    }
  }

  return false;
}