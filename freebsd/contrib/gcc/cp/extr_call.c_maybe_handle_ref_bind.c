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
struct TYPE_5__ {scalar_t__ kind; int /*<<< orphan*/  bad_p; int /*<<< orphan*/  user_conv_p; TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ conversion ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ ck_ref_bind ; 

__attribute__((used)) static tree
maybe_handle_ref_bind (conversion **ics)
{
  if ((*ics)->kind == ck_ref_bind)
    {
      conversion *old_ics = *ics;
      tree type = TREE_TYPE (old_ics->type);
      *ics = old_ics->u.next;
      (*ics)->user_conv_p = old_ics->user_conv_p;
      (*ics)->bad_p = old_ics->bad_p;
      return type;
    }

  return NULL_TREE;
}