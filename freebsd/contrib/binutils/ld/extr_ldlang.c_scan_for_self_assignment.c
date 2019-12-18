#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  name; } ;
struct TYPE_15__ {int /*<<< orphan*/  str; } ;
struct TYPE_14__ {TYPE_8__* child; } ;
struct TYPE_13__ {TYPE_8__* src; int /*<<< orphan*/  dst; } ;
struct TYPE_12__ {TYPE_8__* rhs; TYPE_8__* lhs; } ;
struct TYPE_11__ {TYPE_8__* rhs; TYPE_8__* lhs; } ;
struct TYPE_10__ {int node_class; } ;
struct TYPE_17__ {TYPE_7__ name; TYPE_6__ value; TYPE_5__ unary; TYPE_4__ assign; TYPE_3__ trinary; TYPE_2__ binary; TYPE_1__ type; } ;
typedef  TYPE_8__ etree_type ;
typedef  int bfd_boolean ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
#define  etree_assign 135 
#define  etree_binary 134 
#define  etree_name 133 
#define  etree_provide 132 
#define  etree_provided 131 
#define  etree_trinary 130 
#define  etree_unary 129 
#define  etree_value 128 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
scan_for_self_assignment (const char * dst, etree_type * rhs)
{
  if (rhs == NULL || dst == NULL)
    return FALSE;

  switch (rhs->type.node_class)
    {
    case etree_binary:
      return scan_for_self_assignment (dst, rhs->binary.lhs)
	||   scan_for_self_assignment (dst, rhs->binary.rhs);

    case etree_trinary:
      return scan_for_self_assignment (dst, rhs->trinary.lhs)
	||   scan_for_self_assignment (dst, rhs->trinary.rhs);

    case etree_assign:
    case etree_provided:
    case etree_provide:
      if (strcmp (dst, rhs->assign.dst) == 0)
	return TRUE;
      return scan_for_self_assignment (dst, rhs->assign.src);

    case etree_unary:
      return scan_for_self_assignment (dst, rhs->unary.child);

    case etree_value:
      if (rhs->value.str)
	return strcmp (dst, rhs->value.str) == 0;
      return FALSE;

    case etree_name:
      if (rhs->name.name)
	return strcmp (dst, rhs->name.name) == 0;
      return FALSE;

    default:
      break;
    }

  return FALSE;
}