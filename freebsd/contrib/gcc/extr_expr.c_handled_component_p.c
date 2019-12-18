#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
#define  ARRAY_RANGE_REF 134 
#define  ARRAY_REF 133 
#define  BIT_FIELD_REF 132 
#define  COMPONENT_REF 131 
#define  IMAGPART_EXPR 130 
#define  REALPART_EXPR 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
#define  VIEW_CONVERT_EXPR 128 

int
handled_component_p (tree t)
{
  switch (TREE_CODE (t))
    {
    case BIT_FIELD_REF:
    case COMPONENT_REF:
    case ARRAY_REF:
    case ARRAY_RANGE_REF:
    case VIEW_CONVERT_EXPR:
    case REALPART_EXPR:
    case IMAGPART_EXPR:
      return 1;

    default:
      return 0;
    }
}