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
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 int /*<<< orphan*/  build_user_type_conversion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
build_type_conversion (tree xtype, tree expr)
{
  /* C++: check to see if we can convert this aggregate type
     into the required type.  */
  return build_user_type_conversion (xtype, expr, LOOKUP_NORMAL);
}