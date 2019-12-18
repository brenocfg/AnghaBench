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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  TYPE_1__* attrs ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  offset; int /*<<< orphan*/  decl; int /*<<< orphan*/  loc; } ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  attrs_pool ; 
 TYPE_1__* pool_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
attrs_list_insert (attrs *listp, tree decl, HOST_WIDE_INT offset, rtx loc)
{
  attrs list;

  list = pool_alloc (attrs_pool);
  list->loc = loc;
  list->decl = decl;
  list->offset = offset;
  list->next = *listp;
  *listp = list;
}