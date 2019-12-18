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
typedef  enum cvalue_type { ____Placeholder_cvalue_type } cvalue_type ;

/* Variables and functions */
 int CONST_VALUE ; 
 int CONST_VALUE_REF ; 

__attribute__((used)) static bool
ipcp_type_is_const (enum cvalue_type type)
{
  if (type == CONST_VALUE || type == CONST_VALUE_REF)
    return true;
  else
    return false;
}