#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* next; } ;
struct TYPE_6__ {scalar_t__ kind; int /*<<< orphan*/  type; TYPE_1__ u; } ;
typedef  TYPE_2__ conversion ;

/* Variables and functions */
 scalar_t__ ck_ambig ; 
 scalar_t__ ck_identity ; 
 scalar_t__ ck_lvalue ; 
 scalar_t__ ck_rvalue ; 
 scalar_t__ ck_user ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
is_subseq (conversion *ics1, conversion *ics2)
{
  /* We can assume that a conversion of the same code
     between the same types indicates a subsequence since we only get
     here if the types we are converting from are the same.  */

  while (ics1->kind == ck_rvalue
	 || ics1->kind == ck_lvalue)
    ics1 = ics1->u.next;

  while (1)
    {
      while (ics2->kind == ck_rvalue
	     || ics2->kind == ck_lvalue)
	ics2 = ics2->u.next;

      if (ics2->kind == ck_user
	  || ics2->kind == ck_ambig
	  || ics2->kind == ck_identity)
	/* At this point, ICS1 cannot be a proper subsequence of
	   ICS2.  We can get a USER_CONV when we are comparing the
	   second standard conversion sequence of two user conversion
	   sequences.  */
	return false;

      ics2 = ics2->u.next;

      if (ics2->kind == ics1->kind
	  && same_type_p (ics2->type, ics1->type)
	  && same_type_p (ics2->u.next->type,
			  ics1->u.next->type))
	return true;
    }
}