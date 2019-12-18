#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_2__ {scalar_t__ identifier; } ;

/* Variables and functions */
 char const* IDENTIFIER_POINTER (scalar_t__) ; 
 TYPE_1__* operator_name_info ; 

__attribute__((used)) static const char *
op_to_string (enum tree_code p)
{
  tree id = operator_name_info[(int) p].identifier;
  return id ? IDENTIFIER_POINTER (id) : "<unknown>";
}