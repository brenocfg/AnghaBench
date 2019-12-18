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
typedef  union parameter_info {int dummy; } parameter_info ;
struct ipcp_formal {union parameter_info cvalue; } ;

/* Variables and functions */

__attribute__((used)) static inline union parameter_info *
ipcp_cval_get_cvalue (struct ipcp_formal *cval)
{
  return &(cval->cvalue);
}