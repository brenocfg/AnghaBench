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
struct TYPE_6__ {int /*<<< orphan*/  loc; int /*<<< orphan*/  offset; int /*<<< orphan*/  decl; struct TYPE_6__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  attrs_list_insert (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attrs_list_member (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
attrs_list_union (attrs *dstp, attrs src)
{
  for (; src; src = src->next)
    {
      if (!attrs_list_member (*dstp, src->decl, src->offset))
	attrs_list_insert (dstp, src->decl, src->offset, src->loc);
    }
}