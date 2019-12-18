#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* attrs ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  offset; int /*<<< orphan*/  decl; int /*<<< orphan*/  loc; } ;

/* Variables and functions */
 int /*<<< orphan*/  attrs_list_clear (TYPE_1__**) ; 
 int /*<<< orphan*/  attrs_pool ; 
 TYPE_1__* pool_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
attrs_list_copy (attrs *dstp, attrs src)
{
  attrs n;

  attrs_list_clear (dstp);
  for (; src; src = src->next)
    {
      n = pool_alloc (attrs_pool);
      n->loc = src->loc;
      n->decl = src->decl;
      n->offset = src->offset;
      n->next = *dstp;
      *dstp = n;
    }
}