#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  conversion_rank ;
typedef  int conversion_kind ;
struct TYPE_7__ {TYPE_2__* next; } ;
struct TYPE_8__ {int user_conv_p; int base_p; int /*<<< orphan*/  bad_p; int /*<<< orphan*/  rank; TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ conversion ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERSION_RANK (TYPE_2__*) ; 
 TYPE_2__* alloc_conversion (int) ; 
#define  ck_base 132 
#define  ck_pmem 131 
#define  ck_ptr 130 
#define  ck_qual 129 
#define  ck_std 128 
 int ck_user ; 
 int /*<<< orphan*/  cr_exact ; 
 int /*<<< orphan*/  cr_std ; 

__attribute__((used)) static conversion *
build_conv (conversion_kind code, tree type, conversion *from)
{
  conversion *t;
  conversion_rank rank = CONVERSION_RANK (from);

  /* We can't use buildl1 here because CODE could be USER_CONV, which
     takes two arguments.  In that case, the caller is responsible for
     filling in the second argument.  */
  t = alloc_conversion (code);
  t->type = type;
  t->u.next = from;

  switch (code)
    {
    case ck_ptr:
    case ck_pmem:
    case ck_base:
    case ck_std:
      if (rank < cr_std)
	rank = cr_std;
      break;

    case ck_qual:
      if (rank < cr_exact)
	rank = cr_exact;
      break;

    default:
      break;
    }
  t->rank = rank;
  t->user_conv_p = (code == ck_user || from->user_conv_p);
  t->bad_p = from->bad_p;
  t->base_p = false;
  return t;
}