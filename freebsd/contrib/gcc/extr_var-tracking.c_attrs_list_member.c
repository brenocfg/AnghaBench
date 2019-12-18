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
typedef  scalar_t__ tree ;
typedef  TYPE_1__* attrs ;
struct TYPE_4__ {scalar_t__ decl; scalar_t__ offset; struct TYPE_4__* next; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */

__attribute__((used)) static attrs
attrs_list_member (attrs list, tree decl, HOST_WIDE_INT offset)
{
  for (; list; list = list->next)
    if (list->decl == decl && list->offset == offset)
      return list;
  return NULL;
}