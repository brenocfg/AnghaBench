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
typedef  int u64 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
#define  H_BUSY 133 
#define  H_CONSTRAINED 132 
#define  H_NOT_ENOUGH_RESOURCES 131 
#define  H_NO_MEM 130 
#define  H_RESOURCE 129 
#define  H_SUCCESS 128 

int ehca2ib_return_code(u64 ehca_rc)
{
	switch (ehca_rc) {
	case H_SUCCESS:
		return 0;
	case H_RESOURCE:             /* Resource in use */
	case H_BUSY:
		return -EBUSY;
	case H_NOT_ENOUGH_RESOURCES: /* insufficient resources */
	case H_CONSTRAINED:          /* resource constraint */
	case H_NO_MEM:
		return -ENOMEM;
	default:
		return -EINVAL;
	}
}