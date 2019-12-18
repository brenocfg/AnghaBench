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
union parameter_info {int /*<<< orphan*/  value; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct ipcp_formal {TYPE_1__ cvalue; } ;
typedef  enum cvalue_type { ____Placeholder_cvalue_type } cvalue_type ;

/* Variables and functions */
 int CONST_VALUE ; 
 int CONST_VALUE_REF ; 

__attribute__((used)) static inline void
ipcp_cval_set_cvalue (struct ipcp_formal *cval, union parameter_info *value,
		      enum cvalue_type type)
{
  if (type == CONST_VALUE || type == CONST_VALUE_REF)
    cval->cvalue.value =  value->value;
}