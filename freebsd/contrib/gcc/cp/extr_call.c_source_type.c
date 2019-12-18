#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {TYPE_2__* next; } ;
struct TYPE_5__ {scalar_t__ kind; int /*<<< orphan*/  type; TYPE_1__ u; } ;
typedef  TYPE_2__ conversion ;

/* Variables and functions */
 scalar_t__ ck_ambig ; 
 scalar_t__ ck_identity ; 
 scalar_t__ ck_user ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static tree
source_type (conversion *t)
{
  for (;; t = t->u.next)
    {
      if (t->kind == ck_user
	  || t->kind == ck_ambig
	  || t->kind == ck_identity)
	return t->type;
    }
  gcc_unreachable ();
}