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
struct aob {int dummy; } ;
struct TYPE_2__ {int (* eadm_start ) (struct aob*) ;} ;

/* Variables and functions */
 TYPE_1__* eadm_ops ; 
 int stub1 (struct aob*) ; 

int scm_start_aob(struct aob *aob)
{
	return eadm_ops->eadm_start(aob);
}