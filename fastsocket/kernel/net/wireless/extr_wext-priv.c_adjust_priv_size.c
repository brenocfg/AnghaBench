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
struct iw_point {int length; } ;
typedef  int __u16 ;

/* Variables and functions */
 int IW_PRIV_SIZE_MASK ; 
 int IW_PRIV_TYPE_MASK ; 
 int* iw_priv_type_size ; 

__attribute__((used)) static int adjust_priv_size(__u16 args, struct iw_point *iwp)
{
	int	num = iwp->length;
	int	max = args & IW_PRIV_SIZE_MASK;
	int	type = (args & IW_PRIV_TYPE_MASK) >> 12;

	/* Make sure the driver doesn't goof up */
	if (max < num)
		num = max;

	return num * iw_priv_type_size[type];
}