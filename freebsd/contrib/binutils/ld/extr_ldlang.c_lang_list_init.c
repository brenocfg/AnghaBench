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
struct TYPE_3__ {int /*<<< orphan*/ * head; int /*<<< orphan*/ ** tail; } ;
typedef  TYPE_1__ lang_statement_list_type ;

/* Variables and functions */

void
lang_list_init (lang_statement_list_type *list)
{
  list->head = NULL;
  list->tail = &list->head;
}