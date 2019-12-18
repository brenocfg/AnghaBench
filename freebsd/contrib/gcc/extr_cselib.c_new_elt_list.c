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
struct elt_list {int /*<<< orphan*/ * elt; struct elt_list* next; } ;
typedef  int /*<<< orphan*/  cselib_val ;

/* Variables and functions */
 int /*<<< orphan*/  elt_list_pool ; 
 struct elt_list* pool_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct elt_list *
new_elt_list (struct elt_list *next, cselib_val *elt)
{
  struct elt_list *el;
  el = pool_alloc (elt_list_pool);
  el->next = next;
  el->elt = elt;
  return el;
}