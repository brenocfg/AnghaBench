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
struct fn_node {struct fn_node* next; int /*<<< orphan*/  (* fn ) () ;} ;
struct TYPE_2__ {struct fn_node* head; } ;

/* Variables and functions */
 TYPE_1__ flush_fn_list ; 
 int /*<<< orphan*/  stub1 () ; 

void __gcov_flush() {
  struct fn_node* curr = flush_fn_list.head;

  while (curr) {
    curr->fn();
    curr = curr->next;
  }
}