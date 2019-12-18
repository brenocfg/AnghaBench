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
struct ipcp_formal {int dummy; } ;

/* Variables and functions */
 scalar_t__ CONST_VALUE ; 
 scalar_t__ CONST_VALUE_REF ; 
 scalar_t__ ipcp_cval_equal_cvalues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ipcp_cval_get_cvalue (struct ipcp_formal*) ; 
 scalar_t__ ipcp_cval_get_cvalue_type (struct ipcp_formal*) ; 

__attribute__((used)) static bool
ipcp_cval_changed (struct ipcp_formal *cval1, struct ipcp_formal *cval2)
{
  if (ipcp_cval_get_cvalue_type (cval1) == ipcp_cval_get_cvalue_type (cval2))
    {
      if (ipcp_cval_get_cvalue_type (cval1) != CONST_VALUE &&
	  ipcp_cval_get_cvalue_type (cval1) != CONST_VALUE_REF)	 
	return false;
      if (ipcp_cval_equal_cvalues (ipcp_cval_get_cvalue (cval1),
				   ipcp_cval_get_cvalue (cval2),
				   ipcp_cval_get_cvalue_type (cval1),
				   ipcp_cval_get_cvalue_type (cval2)))
	return false;
    }
  return true;
}